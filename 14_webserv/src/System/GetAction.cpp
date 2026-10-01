#include <sstream>

#include "GetAction.hpp"

class Action;

/*static std::string htmlEscape(const std::string &str) { //todo use in filenames and other variable strings that will be written into a regular response
    std::string output;
    output.reserve(str.size());

    for (std::string::const_iterator it = str.begin(); it < str.end(); ++it) {
        switch (*it) {
            case '&':  output += "&amp;";  break;
            case '<':  output += "&lt;";   break;
            case '>':  output += "&gt;";   break;
            case '"':  output += "&quot;"; break;
            case '\'': output += "&#39;";  break;
            default:   output += *it;     break;
        }
    }
    return output;
}*/

Response GetAction::_generateAutoIndex()
{
    DIR *dir = opendir(_targetPath.c_str());
    if (!dir)
        throw HttpError(HTTP_FORBIDDEN, "Forbidden").withRequest(*_req); //todo for common statusMessages like this, use const static map of enum to string? share it from response maybe

    std::stringstream html;

    html << "<html><head><title>Directory listing: " << _rawPath
         << "</title></head><body>\n";
    html << "<h1>Directory listing: " << _rawPath << "</h1><hr><pre>\n";

    const struct dirent *entry;
    while ((entry = readdir(dir)) != NULL)
    {
        std::string filename = entry->d_name;

        if (filename == "." || filename == "..") //ignore . and ..
            continue;

        std::string fullPath = Action::pathConcatenate(_targetPath, filename);

        struct stat st;
        if (stat(fullPath.c_str(), &st) == 0)
        {
            if (S_ISDIR(st.st_mode)) // directory paths end in /
                html << "<a href=\"" << filename << "/\">" << filename << "/</a>\n";
            else
                html << "<a href=\"" << filename << "\">" << filename << "</a>\n";
        }
        else
            continue; //no permits to stat the resource
    }

    html << "</pre><hr></body></html>\n";
    const std::string html_str = html.str();

    closedir(dir);

    Response resp(HTTP_OK, html_str);
    resp.addHeader("Content-Length", resp.getBody().length());
    resp.addHeader("Content-Type", Action::getFiletype(".html"));
    resp.setVersion(_req->getVersion());
    resp.setKeepAlive(_req->getKeepAlive());
    return resp;
}

//returns first valid index found in config
const std::string GetAction::_getIndexPath() const {
    std::vector<std::string>::const_iterator it;
    std::vector<std::string>::const_iterator end;

    if (_location != NULL && _location->getIndex().size() > 0) {
        const std::vector<std::string> &vec = _location->getIndex();
        it = vec.begin();
        end = vec.end();
    }
    else { //fallback to server block if index from location is absent
        const std::vector<std::string> &vec = _config->getIndex();
        if (vec.size() == 0)
            throw HttpError(HTTP_FORBIDDEN, "Directory listing not allowed").withRequest(*_req); //no index to check

        it = vec.begin();
        end = vec.end();
    }
    std::string prefix; //prepend root + location path or alias before checking
    if (_location != NULL && _location->getRoot().size() > 0)
        prefix = Action::pathConcatenate(_location->getRoot(), _location->getPathMatch());
    else
        prefix = _config->getRoot();
    for (;it < end; ++it) { //check each index route sequentially. skip if missing, unreadable, or a dir
        const std::string indexPath = Action::pathConcatenate(prefix, *it);

        struct stat filestat;
        if (stat(indexPath.c_str(), &filestat) != 0)
            continue;
        if (S_ISDIR(filestat.st_mode))
            continue;
        
        return indexPath;
    }
    //end of vector, no valid route found
    throw HttpError(HTTP_FORBIDDEN, "Directory listing not allowed").withRequest(*_req); //client trying to GET folder with autoindex disabled, return forbidden
}

Response GetAction::exec() {
    struct stat filestat;
    if (stat(_targetPath.c_str(), &filestat) != 0)
        throw HttpError(HTTP_NOTFOUND, "Resource " + _rawPath + " not found").withRequest(*_req); //use raw path from the request in response to not reveal internal data

    if (access(_targetPath.c_str(), R_OK) != 0)
        throw HttpError(HTTP_FORBIDDEN, "Resource " + _rawPath + " not readable").withRequest(*_req);

    std::string filePath = _targetPath;

    if (S_ISDIR(filestat.st_mode)) { //target is a directory
        if (_rawPath != "/" && _targetPath[_targetPath.size() - 1] != '/')
            _targetPath += '/'; //if its a folder, add trailing slash for consistency with browsers

        if ((_location != NULL && _location->getAutoindex()) || _config->getAutoindex()) //if autoindex is enabled, return directory listing as generated .html
            return _generateAutoIndex();
        else //otherwise return default index files, if none are accesible, return 403 (since it is requesting a folder with directory listing disabled)
            filePath = _getIndexPath();
    }

    //else if (S_ISREG(filestat.st_mode)) { //target is a file
    else {
        if (_targetPath[_targetPath.size() - 1] == '/') //requesting with a trailing slash implies requesting a folder. if a file is found with the same name, it is considered as not found
            throw HttpError(HTTP_NOTFOUND, "Not found").withRequest(*_req);
    }

    std::ifstream infile(filePath.c_str()); //todo stress testing with larger files
    if (!infile)
        throw HttpError(HTTP_SERVER_ERROR, "Resource " + _rawPath + " not available").withRequest(*_req);

    std::ostringstream buffer;
    buffer << infile.rdbuf(); //todo chunked buffering for large files?
    infile.close();

    Response resp(HTTP_OK, buffer.str());
    resp.addHeader("Content-Length", resp.getBody().length());
    resp.addHeader("Content-Type", Action::getFiletype(filePath));
    resp.setVersion(_req->getVersion());
    resp.setKeepAlive(_req->getKeepAlive());
    return resp;
}
