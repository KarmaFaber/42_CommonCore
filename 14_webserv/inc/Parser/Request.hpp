#pragma once

#include <stdint.h>
#include <stdexcept>

#include "Message.hpp"
#include "Client.hpp"
#include "ConfigParser.hpp"

enum HTTPMethod {
    GET,
    POST,
    DELETE
};

class Request: public Message {
	private:
		static const std::string _allowed_path_chars;
    	static const std::map<std::string, HTTPMethod> _methodStringMap;
		HTTPMethod _method;
		std::string _path;
		const Client &_client;
		const ServerConfig *_config;
		const LocationConfig *_loc;

		std::string::size_type _body_start_pos;

		void _populate(const std::string &str, const std::string &linebreak);
		void _throwError();
		void _validatePath(const std::string &path);
		void _parseChunkedBody(const std::string &rawBody);
		void _parseConnectionHeader(const std::string &connection);

    public:
		Request(const std::string &raw_req, const Client &client);

		static std::string methodToString(HTTPMethod method);
		HTTPMethod getMethod() const;
		const std::string& getPath() const;
		const Client &getClient() const;

		const ServerConfig &verifyConfig(const ConfigParser &configParser);
		void parseBody(const std::string &raw_req);

		const ServerConfig *getConfig() const; //todo refactor to serverConfig and LocationConfig
		const LocationConfig *getLocation() const;

		void verifySession(SessionManager &sessionMng);
};
