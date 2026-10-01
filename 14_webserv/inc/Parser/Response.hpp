#pragma once

#include "Message.hpp"
#include "HttpError.hpp"
#include "HttpStatusEnum.hpp"

class Response: public Message {
private:
	static const std::map<HTTPStatus, std::string> _statusMessageMap;

    HTTPStatus _status;
    std::string _customStatusMessage;
	std::string _genFirstLine(void) const;

	void _populate(const std::string &str, const std::string &linebreak);
	void _throwError(void);
	void _parseStatusHeader(const std::string &value);
	void _addFixedHeaders(std::ostringstream &ss) const;

public:
	static const std::string httpVersion;
	static const std::string webservName;

	Response(const HTTPStatus status): _status(status) {};
	Response(const HTTPStatus status, const std::string &body_content): Message(body_content), _status(status) {};
	Response(const HTTPStatus status, const std::string &statusMessage, const std::string &body): Message(body), _status(status), _customStatusMessage(statusMessage) {};
	Response(const HTTPStatus status, const std::string &statusMessage, const Message &entity): Message(entity), _status(status), _customStatusMessage(statusMessage) {};

	Response(const std::string &cgi_output); //only for cgi, to parse raw response as string

	HTTPStatus getStatus() const;

	std::string toString(void) const;

	void verifySession(SessionManager &sessionMng);
};
