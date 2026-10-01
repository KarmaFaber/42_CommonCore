#include "Request.hpp"
#include "HttpStatusEnum.hpp"
#include "HttpError.hpp"

const std::string Request::_allowed_path_chars = "/-_.~!$?&'()*+,;=:@";

static std::map<std::string, HTTPMethod> initMethodMap() {
	std::map<std::string, HTTPMethod> methodMap;

	//poner aqui todos los enums correspondientes a cada metodo
	methodMap.insert(std::pair<std::string, HTTPMethod>("GET", GET));
	methodMap.insert(std::pair<std::string, HTTPMethod>("POST", POST));
	methodMap.insert(std::pair<std::string, HTTPMethod>("DELETE", DELETE));

	return methodMap;
}

const std::map<std::string, HTTPMethod> Request::_methodStringMap = initMethodMap();

std::string Request::methodToString(HTTPMethod method) {
    std::map<std::string, HTTPMethod>::const_iterator it = _methodStringMap.begin();
    for (; it != _methodStringMap.end(); ++it) { //inefficient O(n) lookup, but here its for a map thats going to have 3 or 4 length at worst
        if (it->second == method)
            return it->first;
    }
    return "";
}

void Request::_throwError() {
    throw HttpError(HTTP_CLIENT_ERROR, "Bad Request").withRequest(*this);
}

static const LocationConfig *getTargetLocation(const std::string &reqPath, const ServerConfig &serverConf) {
    const LocationConfig* loc = NULL;
    size_t pathLen = 0; //track matched path length

    const std::vector<LocationConfig> &locations = serverConf.getLocations();
    for (size_t i = 0; i < locations.size(); ++i) {
        const std::string &locPath = locations[i].getPathMatch();

        if (reqPath.compare(0, locPath.size(), locPath) == 0) {
            if (locPath.size() > pathLen) { //longest match takes priority. /upload/specific will be prioritized over /upload
                loc = &locations[i];
                pathLen = locPath.size();
            }
        }
    }

    return loc;
}

void Request::_validatePath(const std::string &path) {
    if (path.empty() || path[0] != '/') //must start with slash
        _throwError();
    
    //reject relative paths
    std::string::size_type it = path.find("/.");
    while (it != std::string::npos) {
        if (it != std::string::npos && (path[it + 2] == '/' || path[it + 2] == '?' || path[it + 2] == '\0'))
            _throwError();
        it = path.find("/.", it + 1);
    }

    it = path.find("/..");
    while (it != std::string::npos) {
        if (it != std::string::npos && (path[it + 3] == '/' || path[it + 3] == '?' || path[it + 3] == '\0'))
            _throwError();
        it = path.find("/..", it + 1);
    }

    for (it = 0; it < path.size(); it++) {
        if (!std::isalnum(path[it]) && _allowed_path_chars.find(path[it]) == std::string::npos)
            _throwError(); //reject any char not alphanumeric and not specifically allowed
    }
}

void Request::_parseChunkedBody(const std::string &rawBody) {
    std::string::size_type prev = 0;
    std::string::size_type pos;

    while (true) {
        pos = rawBody.find("\r\n", prev);
        if (pos == std::string::npos)
            _throwError();

        std::string chunkSizeStr = rawBody.substr(prev, pos - prev);
        char *end;
        errno = 0;
        long chunkSize = std::strtol(chunkSizeStr.c_str(), &end, 16);
        if (errno != 0 || *end != '\0' ||  chunkSize < 0)
            _throwError();

        if (chunkSize == 0) {
            if (rawBody.compare(pos, 2, "\r\n") != 0 || rawBody.compare(pos + 2, 2, "\r\n") != 0 || pos + 4 != rawBody.length())
                _throwError();
            return; //empty chunk with linebreak, end of body
        }

        _body_size += chunkSize;
        if ((_loc != NULL && _loc->getClientMaxBodySize() > 0 && _body_size > _loc->getClientMaxBodySize()) ||
                (_config->getClientMaxBodySize() > 0 && _body_size > _config->getClientMaxBodySize()))
            throw HttpError(HTTP_CONTENT_TOO_LARGE, "Content Too Large").withRequest(*this);
        
        pos += 2; //skip newline delimiter
        if (pos + chunkSize > rawBody.length())
            _throwError();

        if (rawBody.compare(pos + chunkSize, 2, "\r\n") != 0)
            _throwError(); //end of chunk should always be linebreak

        _body += rawBody.substr(pos, chunkSize);

        prev = pos + chunkSize + 2; //skip linebreak at end of chunk
    }
}

Request::Request(const std::string &raw_req, const Client &client): _client(client), _config(NULL), _loc(NULL) {
    std::string::size_type pos = raw_req.find("\r\n");
    if (pos == std::string::npos) //empty request error case
        _throwError();
        //throw HttpError(HTTP_CLIENT_ERROR, "Empty request");

    std::string first_line = raw_req.substr(0, pos);
    if (first_line.find("\r") != std::string::npos || first_line.find("\n") != std::string::npos) {
        _throwError(); //linebreaks not allowed
    }

	std::stringstream ss(first_line);
    std::string method_str;
    if (!getline(ss, method_str, ' '))
        _throwError();

    std::string path;
    if (!getline(ss, path, ' '))
        _throwError();
        //throw HttpError(HTTP_CLIENT_ERROR, "Invalid path");
    _validatePath(path);

    std::string version;
    if (!getline(ss, version, ' '))
        _throwError();
    
    if (version == "HTTP/1.0")
		setVersion(HTTP_1_0);
    else if (version == "HTTP/1.1")
		setVersion(HTTP_1_1);
    else
		throw HttpError(HTTP_VERSION_NOT_SUPPORTED, "HTTP Version Not Supported");

	//init and store internal variables
    _path = path;

	std::map<std::string, HTTPMethod>::const_iterator it = this->_methodStringMap.find(method_str);
    if (it == this->_methodStringMap.end())
        throw HttpError(HTTP_NOT_IMPLEMENTED, "Not Implemented").withRequest(*this);
    _method = it->second;

    _keep_alive = _version == HTTP_1_1; //default to true in 1.1, false in 1.0

    _populate(raw_req, "\r\n"); //populate request object headers
}

HTTPMethod Request::getMethod() const{
	return _method;
}

const std::string &Request::getPath() const {
    return _path;
}

const Client &Request::getClient() const {
	return _client;
}

const ServerConfig *Request:: getConfig() const {
    return _config;
}

const LocationConfig *Request::getLocation() const {
    return _loc;
}

static std::string trimSpace(std::string str) {
    std::string::size_type start = str.find_first_not_of(" \t");
    if (start == std::string::npos)
        return "";

    std::string::size_type end = str.find_last_not_of(" \t");

    return str.substr(start, end - start + 1);
}

void Request::_parseConnectionHeader(const std::string &connection) {
    if (connection.empty()) //also throw error if it is only whitespace?
        _throwError();

    std::stringstream ss(connection);
    std::string token;

    bool locked = false;
    while (std::getline(ss, token, ',')) {
        token = trimSpace(token); //"keep-alive, close" is just as valid as "  keep-alive,     close   "

        if (token.empty())
            _throwError();

        for (std::string::iterator it = token.begin(); it < token.end(); ++it)
            *it = std::tolower(*it); //tokens ignore casing

        if (token == "close") {
            locked = true; //close always takes priority
            _keep_alive = false;
        }

        else if (token == "keep-alive" && !locked)
            _keep_alive = true;
    }
}

void Request::_populate(const std::string &str, const std::string &linebreak) {
    std::string::size_type pos = str.find(linebreak);
    if (pos == std::string::npos) //empty request
        _throwError();

    //parse headers
    pos += linebreak.length(); //skip first linebreak
    pos += _populateHeaders(str.substr(pos), linebreak); //skip all the headers

    if (_headers.find("connection") != _headers.end())
        _parseConnectionHeader(_headers.find("connection")->second);
    
    if (_version == HTTP_1_1 && _headers.find("host") == _headers.end())
        _throwError(); // HTTP/1.1 must always have Host header

    _body_start_pos = pos; //save start position for later parseBody call
}

static bool serverNameMatch(const std::string &hostname, const std::vector<std::string> &serverNames) {
    for (std::vector<std::string>::const_iterator it = serverNames.begin(); it < serverNames.end(); it++) {
        if (*it == hostname)
            return true;
    }

    return false;
}

const ServerConfig &Request::verifyConfig(const ConfigParser &configParser) {
    std::string hostname = "";
    if (_headers.find("host") != _headers.end())
        hostname = _headers.find("host")->second;
    std::string::size_type it = hostname.find(':');
    if (it != std::string::npos)
        hostname = hostname.substr(0, it); //strip port from hostname //todo validate port string is valid, and equal to the port number from client

    const std::vector<ServerConfig> &servers = configParser.getServers();

    if (!hostname.empty()) {
        for (std::vector<ServerConfig>::const_iterator it = servers.begin(); it < servers.end(); it++) {
            if (it->getPort() == _client.getSockPort() && serverNameMatch(hostname, it->getServerNames())) {
                _config = &(*it);
                break;
            }
        }
    }

    //if no host header or no hostname match, default to first server block with matching port
    if (_config == NULL) {
        for (std::vector<ServerConfig>::const_iterator it = servers.begin(); it < servers.end(); it++) {
            if (it->getPort() == _client.getSockPort()) {
                _config = &(*it);
                break;
            }
        }
    }

    if (_config == NULL)
        throw std::runtime_error("No matching config found for request"); //no matching port for request, which should never happen
    
    _loc = getTargetLocation(_path, *_config);

    //config checks here (except for enforcing body size limit)
    if (((_loc != NULL && !_loc->isMethodAllowed(methodToString(_method)))) ||
            !_config->isMethodAllowed(methodToString(_method)))
        throw HttpError(HTTP_INVALID_METHOD, "Unsupported method").withRequest(*this);

    return *_config;
}

void Request::parseBody(const std::string &raw_req) {
    if (_headers.find("content-type") != _headers.end() && _headers.find("content-length") == _headers.end() && _body_encoding == RAW) //dont throw error if encoding is not raw
        _throwError(); //request with content-type but no defined content-length should be rejected

    //remainder of request is body
    if (_body_encoding == RAW) {
        _body = raw_req.substr(_body_start_pos);
        if (_body.length() != _body_size ||(_loc != NULL && _body_size > _loc->getClientMaxBodySize()) ||
            _body_size > _config->getClientMaxBodySize()) //if body is empty, Content-Length header must be 0 or absent entirely
            throw HttpError(HTTP_CONTENT_TOO_LARGE, "Content Too Large").withRequest(*this);
    }
    //else if (_body_encoding == CHUNKED) {
    else {
        if (_body_size != 0 || _headers.find("content-length") != _headers.end())
            _throwError(); //chunked requests shouldnt try to set body size

        _parseChunkedBody(raw_req.substr(_body_start_pos));
    }

}

void Request::verifySession(SessionManager &sessionMng) {
    if (_headers.find("cookie") != _headers.end()) {
        std::string cookie = _headers.find("cookie")->second;

        std::stringstream ss(cookie);
        std::string token;

        while (std::getline(ss, token, ';')) {
            token = trimSpace(token);
            if (token.empty())
                continue;

            std::string::size_type it = token.find('=');
            if (it == std::string::npos)
                continue;
            
            std::string name = trimSpace(token.substr(0, it));
            if (name != _session_fieldname) //for this project, only consider the session cookie
                continue;

            std::string value = trimSpace(token.substr(it + 1));

            _session = sessionMng.getSession(value);

            break; //in case of duplicated cookies, the first or the last should prevail. in this project there is not much difference
        }
    }
}
