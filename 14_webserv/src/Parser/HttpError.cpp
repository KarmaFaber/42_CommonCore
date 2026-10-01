#include "HttpError.hpp"
#include "Request.hpp"
#include <sstream>

static std::string buildErrorMessage(const HTTPStatus status, const std::string &message) {
    std::stringstream ss;
    ss << status << " " << message;
    return ss.str();
}

HttpError::HttpError(const HTTPStatus status): _status(status), _statusMessage(""), _config(NULL), _loc(NULL), _what(buildErrorMessage(_status, _statusMessage)) {
    _version = HTTP_1_0; //default to 1.0
    _keep_alive = false;
}

HttpError::HttpError(const HTTPStatus status, const std::string &statusMessage): _status(status), _statusMessage(statusMessage), _config(NULL), _loc(NULL), _what(buildErrorMessage(_status, _statusMessage)) {
    _version = HTTP_1_0;
    _keep_alive = false;
}

const char *HttpError::what() const throw() {
    return _what.c_str();
}

HTTPStatus HttpError::getStatus() const {
    return _status;
}

const std::string HttpError::getStatusMessage() const {
    return _statusMessage;
}

const ServerConfig *HttpError::getServerConfig() const {
    return _config;
}

const LocationConfig *HttpError::getLocationConfig() const {
    return _loc;
}

HttpVersion HttpError::getVersion() const {
    return _version;
}

bool HttpError::getKeepAlive() const {
    return _keep_alive;
}

HttpError &HttpError::withRequest(const Request &req) {
    _config = req.getConfig();
    _loc = req.getLocation();
    _version = req.getVersion();
    _keep_alive = req.getKeepAlive();
    return *this;
}
