#include <sstream>

#include "Message.hpp"
#include <cctype>
#include <cerrno>
#include <cstdlib>

const std::string Message::_allowed_headerName_chars = "'!#$%&\\*+-.^_`|~";
const std::string Message::_session_fieldname = "bonus-session-id";

static std::string normalizeHeaderKey(const std::string &key) {
    std::string normalized;
    normalized.reserve(key.size());

    for (std::string::const_iterator it = key.begin(); it != key.end(); ++it) {
        normalized += static_cast<char>(std::tolower(static_cast<unsigned char>(*it)));
    }

    return normalized;
}

void Message::addHeader(std::pair<std::string, std::string> pair) {
    pair.first = normalizeHeaderKey(pair.first);
    _checkHeader(pair);
    _headers.insert(pair);
}

void Message::addHeader(const std::string &key, const unsigned int value) {
	std::ostringstream oss;
	oss << value;

    addHeader(std::make_pair(key, oss.str()));
}

void Message::addHeader(const std::string &key, const std::string &value) {
    addHeader(std::make_pair(key, value));
}

Message &Message::setVersion(const HttpVersion ver) {
    _version = ver;
    return *this;
}
HttpVersion Message::getVersion(void) const {
    return _version;
}

std::string Message::versionToString(HttpVersion version) {
    if (version == HTTP_1_0)
		return "HTTP/1.0";
	return "HTTP/1.1";
}

Message &Message::setKeepAlive(const bool keep_alive) {
    _keep_alive = keep_alive;
    return *this;
}

bool Message::getKeepAlive(void) const {
    return _keep_alive;
}

const Session *Message::getSession() const {
    return _session;
}

// returns a header which key is "header", treats empty header the same as absent header
const std::string Message::getHeaderContent(const std::string &header) const {
    std::multimap<std::string, std::string>::const_iterator it;
    it = _headers.find(header);

    if (it == _headers.end()) //not found
        return ""; //return empty

    return it->second;
}

const std::multimap<std::string, std::string> &Message::getHeaders() const
{
    return _headers;
}

bool Message::isHeadersListEmpty() const
{
    return _headers.empty();
}

void    Message::setBody(const std::string &str)
{
    _body = str;
}

const std::string &Message::getBody() const
{
    return (_body);
}

bool Message::isBodyEmpty() const
{
    return _body.empty();
}

//throws HTTP error if the header is invalid
void Message::_checkHeader(std::pair<std::string, std::string> &new_hdr) {
    const std::string &key = new_hdr.first;
    if (key.length() == 0)
        _throwError();
    
    std::string &value = new_hdr.second;

    for (std::string::const_iterator it = key.begin(); it < key.end(); ++it) {
        unsigned char c = static_cast<unsigned char>(*it);
        if (c < 32 ||c > 126) //reject non ASCII in header name
            _throwError();
        if (!std::isalnum(c) && _allowed_headerName_chars.find(c) == std::string::npos) //reject any char that is not alphanumeric and not specifically allowed
            _throwError();
    }

    if (key == "content-length") { //even in GET or DELETE, Content-Length value still needs to be valid syntax
        if (_headers.find("content-length") != _headers.end())
            _throwError();
            //throw HttpError(HTTP_CLIENT_ERROR, "Content-Length multiple values");

        if (_headers.find("transfer-encoding") != _headers.end() && _body_encoding != RAW)
            _throwError(); //transfer-encoding other than identity plus content-length is not valid

        errno = 0; //reset errno before syscall
        char *end;
        long body_size = std::strtol(new_hdr.second.c_str(), &end, 10); //todo is this reliable against invalid values?
        if (errno != 0 || *end != '\0' || body_size < 0)
            _throwError();

        _body_size = body_size;
    }

    else if (key == "transfer-encoding") {
        if (value == "chunked") {
            if (_headers.find("content-length") != _headers.end())
                _throwError(); //transfer-encoding other than identity plus content-length is not valid
            _body_encoding = CHUNKED;
        }
        else if (value != "identity")
            throw HttpError(HTTP_NOT_IMPLEMENTED, "Not implemented"); //only support chunked and identity
    }

    else if (key == "content-encoding") {
        if (value != "identity") //only support raw encoding for this project
            throw HttpError(HTTP_UNSUPPORTED_TYPE, "Unsupported media type");
    }

    else if (key == "host" || key == "content-type" ||
            key == "authorization" || key == "proxy-authorization"
            || key == "expect" || key == "expect" || key == "referer"
            || key == "user-agent" || key == "range") { //some headers should never be duplicated
        if (_headers.find(key) != _headers.end())
            _throwError();
    }

    else if (key == "connection") { //some other header values can also be merged by commas, not relevant to this version
        std::multimap<std::string, std::string>::iterator it = _headers.find("connection");
        if (it != _headers.end()) { //merge header values and replace previous one
            value = it->second + ", " + value;
            _headers.erase(it);
        }
    }

    else if (key == "cookie") {
        std::multimap<std::string, std::string>::iterator it = _headers.find("cookie");
        if (it != _headers.end()) { //merge header values and replace previous one
            value = it->second + "; " + value; //cookies are merged with ';' not ','
            _headers.erase(it);
        }
    }
}

std::pair<std::string, std::string> Message::_parseHeader(const std::string &header_str) {
    if (header_str.find("\r") != std::string::npos || header_str.find("\n") != std::string::npos) //linebreaks not allowed
        _throwError();

    std::string rawKey;
    std::string value;

    std::string::size_type pos = header_str.find(": ");
    if (pos == std::string::npos)
        _throwError();

    rawKey = header_str.substr(0, pos);
    std::string key = "";
    for (std::string::const_iterator it = rawKey.begin(); it < rawKey.end(); ++it) {
        key += std::tolower(*it);
    }
	value = header_str.substr(pos + 2);

	return std::make_pair(key, value);
}

std::string::size_type Message::_populateHeaders(const std::string &str, const std::string &linebreak) {
    std::string::size_type prev = 0;
    std::string::size_type pos;


    while ((pos = str.find(linebreak, prev)) != std::string::npos)
    {
        //std::cout << "Parsing line: " << str.substr(prev, pos - prev) << std::endl;
        if (str.substr(prev, pos - prev).length() <= 1) //empty line, headers over
            break;
        addHeader(_parseHeader(str.substr(prev, pos - prev)));
        prev = pos + linebreak.length();
    }

    if (_headers.size() > 0 && str.find(linebreak, prev) != prev) //linebreak should be next, right after headers
        throw HttpError(HTTP_CLIENT_ERROR, "Parser: No linebreak after headers"); //otherwise reject with HTTP error, request malformed
    
    else if (_headers.size() == 0 && (pos != 0 || str.compare(0, linebreak.size(), linebreak) != 0)) //empty headers is only acceptable in a request with nothing else BUT the first line
        _throwError();

    if (pos == 0) //not a single linebreak, no headers
        return 0;

    return pos + 2; //return start of body position
}
