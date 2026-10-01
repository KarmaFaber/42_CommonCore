#include "PostAction.hpp"

class Action;

Response PostAction::_createFile(const bool createNewFile) {
    std::ofstream outFile(_targetPath.c_str());

    if (outFile.is_open()) {
        outFile << _body;
        outFile.close();
        std::cout << "POST: Created file in " << _targetPath << std::endl;
        if (createNewFile) {
            Response resp(HTTP_CREATED, _body);
            resp.addHeader("Content-Length", _body.length());
            resp.addHeader("Content-Type", Action::getFiletype(_targetPath));
            resp.addHeader("Location", _rawPath); //new location is the same as the original request
            resp.setVersion(_req->getVersion());
            resp.setKeepAlive(_req->getKeepAlive());
            return resp;
        }
        else {
            Response resp(HTTP_OK);
            resp.addHeader("Content-Length", "0"); //not required, but its good practice
            resp.setVersion(_req->getVersion());
            resp.setKeepAlive(_req->getKeepAlive());
            return resp;
        }
    }
    else {
        std::cout << "error when opening file: " << _targetPath << std::endl;
        throw HttpError(HTTP_SERVER_ERROR, "Could not open file").withRequest(*_req);
    }
}

static std::string getTargetUploadPath(const std::string &upload_path, const std::string &target_path, const std::string &root_path) {
    std::string::size_type it = target_path.rfind('/');
    std::string filename = "";

    if (it == std::string::npos) //target path is only the filename
        filename = target_path;
    else
        filename = target_path.substr(it + 1);

    return Action::pathConcatenate(Action::pathConcatenate(root_path, upload_path), filename);
}


Response PostAction::exec() {
    if (_targetPath[_targetPath.size() - 1] == '/')
            throw HttpError(HTTP_FORBIDDEN, "Cannot post to folder").withRequest(*_req); //using a trailing slash means the client is looking for a folder

    if (_location != NULL && !_location->getUploadPath().empty())
        _targetPath = getTargetUploadPath(_location->getUploadPath(), _targetPath, _location->getRoot());
    //else if (!_config->getUploadPath().empty())
    else
        _targetPath = getTargetUploadPath(_config->getUploadPath(), _targetPath, _config->getRoot());

    //if it already exists, check if its a folder. otherwise should be fine to overwrite
    struct stat filestat;
    if (stat(_targetPath.c_str(), &filestat) != 0) //create file if it doesnt exist, return 201 Created
        return _createFile(true);
    else { //if it already exists, overwrite and return 200 HTTP_OK
        if (S_ISDIR(filestat.st_mode))
            throw HttpError(HTTP_INVALID_METHOD, "Cannot post to folder").withRequest(*_req);
        if (access(_targetPath.c_str(), W_OK) != 0)
            throw HttpError(HTTP_FORBIDDEN, "Cannot write to resource").withRequest(*_req);
        //if (S_ISREG(filestat.st_mode)) {
            //existing file, overwrite and return 200 HTTP_OK
        //}
        return _createFile(false);
    }
}
