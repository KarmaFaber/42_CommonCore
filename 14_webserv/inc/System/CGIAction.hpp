#pragma once

#include <string>
#include <map>
#include "Request.hpp"
#include "Response.hpp"
#include "HttpError.hpp"
#include "Action.hpp"

#define CGIPOLLTIMEOUT 1000 //milliseconds
#define CGITOTALTIMEOUT 5 //seconds

class CGIAction: public Action {
	private:
		//fixed cgi env vars
		static const std::string _gatewayInterface;
		static const std::string _redirectStatus;

		static const int _cgiMaxResponseSize = 100 * 1024; //100KB should be more than enough for flat html responses

		const std::string _cgiPath;
		const std::string _pathInfo;
		const std::string _queryString;
		const std::string &_reqBody;
		const HTTPMethod _method; //in cgi, method can be different

		void		_buildEnv(const Request &req);
		char		**_envToArray() const;
		std::string	_cgi_execute(void);

		std::map<std::string, std::string> _env;

	public:
		CGIAction(const Request &req, const std::string &cgiPath, const std::string &path_leftover);
		Response exec(void);
};
