#include "Response.hpp"
#include <sstream>
#include <utility>
#include <ctime>

static std::map<HTTPStatus, std::string> initStatusMap() {
	std::map<HTTPStatus, std::string> statusMap;

	//fill out with default messages for common status
	statusMap.insert(std::make_pair(HTTP_OK, "OK"));
	statusMap.insert(std::make_pair(HTTP_CREATED, "Created"));
	statusMap.insert(std::make_pair(HTTP_NOCONTENT, "No Content"));
	statusMap.insert(std::make_pair(HTTP_REDIRECTION, "Moved Permanently"));
	statusMap.insert(std::make_pair(HTTP_FOUND, "Found"));
	statusMap.insert(std::make_pair(HTTP_CLIENT_ERROR, "client error"));
	statusMap.insert(std::make_pair(HTTP_SERVER_ERROR, "server error"));

	return statusMap;
}

const std::string Response::webservName = "SlopServer/1.0";
const std::map<HTTPStatus, std::string> Response::_statusMessageMap = initStatusMap();

void Response::_throwError() {
	throw HttpError(HTTP_SERVER_ERROR, "Internal Server Error"); //could add config here
}

void Response::_parseStatusHeader(const std::string &value) {
	if (value.length() < 5) //shortest status header value would be XXX A, where the single char is the entire status message, separated by a space
		_throwError();

	if (!std::isdigit(value[0]) || !std::isdigit(value[1]) || !std::isdigit(value[2])) //first three chars should be the status number
		_throwError();

	int statusInt = ((value[0] - '0') * 100) + ((value[1] - '0') * 10) + (value[2] - '0');
	if (statusInt < 100 || statusInt > 599)
		_throwError();
	_status = static_cast<HTTPStatus>(statusInt); //this does not throw error even if statusInt is not defined in the enum

	std::string::size_type messageStart = value.find_first_not_of(" \t\n", 3);
	if (messageStart == std::string::npos) //message cannot be whitespace
		_throwError();
	_customStatusMessage = value.substr(messageStart);
}

Response::Response(const std::string &cgi_output) {
	//for cgi allow both "\r\n" and "\n" linebreaks, for flexibility of the cgi scripts
	if (cgi_output.find("\r\n\r\n") != std::string::npos)
		_populate(cgi_output, "\r\n");
	else if (cgi_output.find("\n\n") != std::string::npos)
		_populate(cgi_output, "\n");
	else
		_throwError(); //no end of response

	std::multimap<std::string, std::string>::const_iterator hdr = _headers.find("content-type");
	if ((hdr == _headers.end() || hdr->second.empty()) && _body.size() > 0)
		_throwError(); //if body is present and Content-Type is not set, throw error, it is mandatory in cgi responses

	hdr = _headers.find("status");
	if (hdr == _headers.end()) { //status header absent
		if (_headers.find("location") != _headers.end())
			_status = HTTP_FOUND; //if Location header but no Status, default to 302
		else
			_status = HTTP_OK; //if neither Location nor Status, default to 200
	}
	else { //parse Status header, and remove from headers
		_parseStatusHeader(hdr->second);
		_headers.erase(hdr->first);
	}
}

HTTPStatus Response::getStatus() const 
{ 
	return _status; 
}

std::string Response::_genFirstLine(void) const {
	std::ostringstream oss;
	std::string statusMessage;
	if (this->_customStatusMessage.length() > 0) //prioritize custom message if it exists
		statusMessage = this->_customStatusMessage;
	else
	{
		std::map<HTTPStatus, std::string>::const_iterator msg = _statusMessageMap.find(this->_status);
		if (msg == _statusMessageMap.end())
			statusMessage = "Unknown";
		else
			statusMessage = msg->second;
	}

	oss << Message::versionToString(_version) << ' ' << static_cast<int>(this->_status) << ' ' << statusMessage;
	return oss.str();
}

static std::string getHttpDate() {
    char buf[64];
    std::time_t t = std::time(0);
    std::tm gm = *std::gmtime(&t);

    // Format: "Day, DD Mon YYYY HH:MM:SS GMT"
    std::strftime(buf, sizeof(buf), "%a, %d %b %Y %H:%M:%S GMT", &gm);
    return std::string(buf);
}


void Response::_addFixedHeaders(std::ostringstream &ss) const { //headers added to all requests
	ss << "\r\n" << "Date: " << getHttpDate();
	if (_keep_alive)
		ss << "\r\n" << "Connection: keep-alive";
	else
		ss << "\r\n" << "Connection: close";
	ss << "\r\n" << "Server: " << webservName;
}

std::string Response::toString(void) const {
	std::ostringstream result;
    std::map<std::string, std::string>::const_iterator it = _headers.begin();
    std::map<std::string, std::string>::const_iterator ed = _headers.end();

    result << _genFirstLine();

	_addFixedHeaders(result);

	if (_headers.find("content-length") == _headers.end())
		result << "\r\n" << "Content-Length: " << _body.size();

    for (; it != ed; ++it) {
        result << "\r\n" << it->first + ": " + it->second;
	}

	result << "\r\n\r\n";

    if (!_body.empty())
        result << _body;

    return result.str();
}

void Response::_populate(const std::string &str, const std::string &linebreak) {
    std::string::size_type it = str.find(linebreak);
    if (it == std::string::npos) //empty request error case
        _throwError();
        //throw HttpError(HTTP_CLIENT_ERROR, "Empty request");

    //parse headers
    it = _populateHeaders(str, linebreak);

    if (it >= str.length()) //end of request, no body
        return;

    _body = str.substr(it); //remainder of request is body
	if (_headers.find("content-length") != _headers.end() && _body.size() != _body_size) //Content-Length header can be absent in response, but if its not, it must have valid value
		_throwError();
}

void Response::verifySession(SessionManager &sessionMng) {
	if (_headers.find("bonus-create-session") != _headers.end() &&
			_headers.find("bonus-create-session")->second == "yes") {
		std::map<std::string, std::string>::iterator it = _headers.find("bonus-username");
		std::string username;
		if (it != _headers.end()) {
			username = it->second;
			_headers.erase(it);
		}
		it = _headers.find("bonus-email"); //if there are more fields, use a string array for field names, and a loop for storing all of them in a session
		std::string email;
		if (it != _headers.end()) {
			email = it->second;
			_headers.erase(it);
		}

		_headers.erase("bonus-create-session");

		std::string sessionId = sessionMng.registerSession(Session(username, email));
		_headers.insert(std::make_pair("set-cookie", _session_fieldname + "=" + sessionId + "; Path=/"));
	}

	else if (_headers.find("bonus-delete-session") != _headers.end()) {
		if (!sessionMng.deleteSession(_headers.find("bonus-delete-session")->second)) {
			//session to be deleted not found
		}
		_headers.erase("bonus-delete-session");
		_headers.insert(std::make_pair("set-cookie", _session_fieldname + "=; Path=/; Max-Age=0")); //delete bonus-session-id cookie from the client
	}
}
