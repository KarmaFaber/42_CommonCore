#pragma once

#include <string>
#include "HttpStatusEnum.hpp"
#include "ServerConfig.hpp"
#include "HttpVersionEnum.hpp"

class Request;

class HttpError : public std::exception {
	private:
		static const std::string	_default_body; //for error fallback, generic response
		const HTTPStatus			_status;
		const std::string			_statusMessage;
		const ServerConfig			*_config;
		const LocationConfig		*_loc;
		HttpVersion					_version;
		bool						_keep_alive;

		const std::string			_what;

	public:
		HttpError(const HTTPStatus status);
		HttpError(const HTTPStatus status, const std::string &statusMessage);

		HTTPStatus				getStatus() const;
		const	std::string		getStatusMessage() const;
		const	ServerConfig	*getServerConfig() const;
		const	LocationConfig	*getLocationConfig() const;

		HttpVersion getVersion() const;
		bool getKeepAlive() const;

		HttpError &withRequest(const Request &req);

		const char *what() const throw();

		~HttpError() throw() {};
};
