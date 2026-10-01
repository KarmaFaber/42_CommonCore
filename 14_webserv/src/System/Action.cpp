#include "Action.hpp"
#include "RedirectAction.hpp"
#include "GetAction.hpp"
#include "PostAction.hpp"
#include "DeleteAction.hpp"
#include "CGIAction.hpp"

//using a static string map. dynamic mime type detection would be overkill for this project
static std::map<std::string, std::string> buildFiletypeMap() {
    std::map<std::string, std::string> filetypeMap;

    filetypeMap[".html"] = "text/html";
    filetypeMap[".htm"]  = "text/html";
    filetypeMap[".css"]  = "text/css";
    filetypeMap[".js"]   = "application/javascript";

    filetypeMap[".json"] = "application/json";
    filetypeMap[".xml"]  = "application/xml";
    filetypeMap[".txt"]  = "text/plain";

    filetypeMap[".png"]  = "image/png";
    filetypeMap[".jpg"]  = "image/jpeg";
    filetypeMap[".jpeg"] = "image/jpeg";
    filetypeMap[".gif"]  = "image/gif";
    filetypeMap[".bmp"]  = "image/bmp";
    filetypeMap[".ico"]  = "image/x-icon";
    filetypeMap[".svg"]  = "image/svg+xml";

    filetypeMap[".pdf"]  = "application/pdf";
    filetypeMap[".zip"]  = "application/zip";
    filetypeMap[".gz"]   = "application/gzip";
    filetypeMap[".tar"]  = "application/x-tar";

    filetypeMap[".mp3"]  = "audio/mpeg";
    filetypeMap[".wav"]  = "audio/wav";
    filetypeMap[".ogg"]  = "audio/ogg";

    filetypeMap[".mp4"]  = "video/mp4";
    filetypeMap[".webm"] = "video/webm";
    filetypeMap[".mpeg"] = "video/mpeg";

    filetypeMap[".py"] = "text/plain";
    filetypeMap[".php"] = "text/plain";

    return filetypeMap;
}

const std::map<std::string, std::string> Action::_filetypeMap = buildFiletypeMap();
const std::string Action::_defaultFiletype = "application/octet-stream";

static const std::string getTargetPath(const std::string &path, const ServerConfig *serverConf, const LocationConfig *loc) {
    if (loc != NULL && loc->getRoot().length() > 0) //location takes priority
        return Action::pathConcatenate(loc->getRoot(), path);
    else { //if location has no root, fallback to server
        if (serverConf->getRoot().length() > 0)
            return Action::pathConcatenate(serverConf->getRoot(), path); //if no matching location or has empty root, default to server root
        else
            throw std::runtime_error("Server without root"); //invalid config, should have been caught at startup
    }
}

Action::Action(const Request &req): _req(&req), _config(req.getConfig()), _location(req.getLocation()), _session(req.getSession()), _targetPath(getTargetPath(req.getPath(), _config, _location)), _rawPath(req.getPath()) {
    if (_location != NULL && !_location->isMethodAllowed(req.methodToString(req.getMethod())))
        throw std::runtime_error("System: Forbidden method requested"); //this should have been caught at request constructor
    else if (!_config->isMethodAllowed(req.methodToString(req.getMethod()))) { //fallback on server
        throw std::runtime_error("System: Forbidden method requested");
    }

    if ((_location->getClientMaxBodySize() > 0 && req.getBody().length() > _location->getClientMaxBodySize()) || (_config->getClientMaxBodySize() > 0 && req.getBody().length() > _config->getClientMaxBodySize()))
        throw std::runtime_error("System: Request body bigger than allowed by config"); //use runtime_error, since it should have been caught by parser
}

const std::string &Action::getFiletype(const std::string &targetPath) { //get mime type from extension, according to local static map
    std::string::size_type str_it = targetPath.find_last_of('/');
    std::string filename;

    if (str_it == std::string::npos)
        filename = targetPath;
    else
        filename = targetPath.substr(str_it + 1);

    str_it = filename.find_last_of('.');
    if (str_it == std::string::npos)
        return Action::_defaultFiletype;
    const std::string rawExtension = filename.substr(str_it);
    std::string extension = "";
    for (std::string::const_iterator it = rawExtension.begin(); it < rawExtension.end(); ++it)
        extension += std::tolower(*it);

    const std::map<std::string, std::string>::const_iterator filetype = Action::_filetypeMap.find(extension);

    if (filetype != Action::_filetypeMap.end())
        return filetype->second;
    
    return Action::_defaultFiletype;
}

std::string Action::pathConcatenate(const std::string &path1, const std::string &path2) {
    if (path1.length() == 0)
        return path2;
    if (path2.length() == 0)
        return path1;

    if (path1[path1.size() - 1] == '/') {
        if (path2[0] == '/')
            return path1 + path2.substr(1);
        else
            return path1 + path2;
    }
    else {
        if (path2[0] == '/')
            return path1 + path2;
        else
            return path1 + '/' + path2;
    }
}

static std::string getCgiPath(const std::string &path, const ServerConfig *serverConf, const LocationConfig *loc, std::string &cgiPath) {
    const std::map<std::string, std::string> &cgis = loc->getCgis();

    if (loc != NULL && cgis.size() > 0) {
        for (std::map<std::string, std::string>::const_iterator it = cgis.begin(); it != cgis.end(); ++it) {
            const std::string &cgi_ext = it->first;
            std::string::size_type ext_pos = path.find(cgi_ext);
            while (ext_pos != std::string::npos) {
                ext_pos += cgi_ext.length(); //go to where the extension ends
                const std::string fullPath = getTargetPath(path.substr(0, ext_pos), serverConf, loc);
                //it gets uploaded without execution rights, user cant run something they uploaded
                if ((ext_pos == path.size() || path[ext_pos] == '/' || path[ext_pos] == '?') && access(fullPath.c_str(), X_OK) == 0) {
                    cgiPath = it->second; //save cgi executable path
                    return path.substr(ext_pos); //cgi path info is everything after cgi extension
                }

                ext_pos = path.find(cgi_ext, ext_pos);
            }
        }
    }

    return " "; //use empty string to differentiate from empty path info ""
}

Action *buildAction(const Request &req) {
    if (req.getConfig()->getReturnUrl().second.size() > 0)
        return new RedirectAction(req.getConfig()->getReturnUrl(), req.getVersion(), req.getKeepAlive()); //redirect always takes priority

    const LocationConfig *loc = req.getLocation();
    if (loc != NULL && loc->getReturnUrl().second.size() > 0)
        return new RedirectAction(loc->getReturnUrl(), req.getVersion(), req.getKeepAlive()); //redirect always takes priority

    const ServerConfig *serverConf = req.getConfig();

    std::string cgiPath = ""; //cgi executable path
    const std::string path_leftover = getCgiPath(req.getPath(), serverConf, loc, cgiPath);
    if (path_leftover != " ") //cgi overrides other methods
        return new CGIAction(req, cgiPath, path_leftover);

    switch (req.getMethod()) { //not redirect and not cgi, use standard HTTP methods
        case GET:
            return new GetAction(req);
        case POST:
            return new PostAction(req);
        case DELETE:
            return new DeleteAction(req);
        default:
            throw std::runtime_error("Unknown action type"); //throw runtime exception since this should have been caught sooner
    }
}
