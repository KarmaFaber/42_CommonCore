#pragma once

#include <map>
#include <string>
#include "HttpError.hpp"
#include "HttpVersionEnum.hpp"
#include "SessionManager.hpp"

enum BodyEncoding {
    RAW, //identity is treated the same as raw, since it still needs content-length
    CHUNKED
};

class Message {
    protected:
        static const std::string _allowed_headerName_chars; //reject every request with a header name that is not alphanumeric and not included here
        static const std::string _session_fieldname;

		HttpVersion	_version;
        bool _keep_alive;
        std::multimap<std::string, std::string> _headers;
        std::string _body;
        std::string::size_type _body_size;
        BodyEncoding _body_encoding; //default to raw
        const Session *_session;

        void _checkHeader(std::pair<std::string, std::string> &new_hdr);
        std::pair<std::string, std::string> _parseHeader(const std::string &header_str);

        std::string::size_type _populateHeaders(const std::string &str, const std::string &linebreak);

        virtual void _populate(const std::string &str, const std::string &linebreak) = 0;
        virtual void _throwError(void) = 0;

public:
        public:
            Message(): _version(HTTP_1_0), _keep_alive(false), _headers(), _body(""), _body_size(0), _body_encoding(RAW), _session(NULL) {};
            Message(const std::string &body_content): _version(HTTP_1_0), _keep_alive(false), _body(body_content), _body_size(0), _body_encoding(RAW), _session(NULL) {};
            Message(const Message &other): _version(other._version), _keep_alive(other._keep_alive), _headers(other.getHeaders()), _body(other.getBody()), _body_size(other._body_size), _body_encoding(other._body_encoding), _session(other._session) {};

		void        addHeader(std::pair<std::string, std::string> pair);
        void        addHeader(const std::string &key, const std::string &value);
		void        addHeader(const std::string &key, const unsigned int value);

		Message		&setVersion(const HttpVersion ver);
		HttpVersion	getVersion(void) const;
        static std::string versionToString(HttpVersion);

        Message		&setKeepAlive(const bool keep_alive);
		bool	    getKeepAlive(void) const;

        const Session *getSession() const;
        virtual void verifySession(SessionManager &sessionMng) = 0; //request matches against existing sessions, response creates new ones

        const       std::multimap<std::string, std::string> &getHeaders() const;
        const       std::string getHeaderContent(const std::string &header) const;
        bool        isHeadersListEmpty() const;

        void        setBody(const std::string &str);
        const       std::string &getBody() const;
        bool        isBodyEmpty() const;
};
