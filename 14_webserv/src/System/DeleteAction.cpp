#include "DeleteAction.hpp"

class Action;

Response DeleteAction::exec() {
    struct stat filestat;
    if (stat(_targetPath.c_str(), &filestat) != 0) {
        if (errno == ENOENT)
            throw HttpError(HTTP_NOTFOUND, "Resource " + _rawPath + " not found").withRequest(*_req);
        throw HttpError(HTTP_FORBIDDEN, "No permissions to delete " + _rawPath).withRequest(*_req);
    }

    if (S_ISDIR(filestat.st_mode))
        throw HttpError(HTTP_FORBIDDEN, "Cannot delete folder").withRequest(*_req);

    if (remove(this->_targetPath.c_str()))
        throw HttpError(HTTP_SERVER_ERROR, "Could not delete resource " + _rawPath).withRequest(*_req);

    Response resp(HTTP_NOCONTENT);
    resp.setVersion(_req->getVersion());
    resp.setKeepAlive(_req->getKeepAlive());
    return resp; //return 204 No Content
}
