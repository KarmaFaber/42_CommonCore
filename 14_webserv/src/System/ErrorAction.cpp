
#include "ErrorAction.hpp"

class Action;

static std::string generateDynamicErrorBody(int status, const std::string& reason)
{
	std::stringstream ss;
	ss << "<html>" << "\r\n";
	ss << "<head><title>" << status << " " << reason << "</title>" << "\r\n";
	ss << "<style>" << "\r\n";
	ss << "body { font-family: 'Courier New', Courier, monospace; color: #000; padding: 50px; line-height: 1.6; }" << "\r\n";
	ss << ".container { max-width: 600px; margin: 0 auto; border: 1px solid #000; padding: 20px; }" << "\r\n";
	ss << "h1 { font-size: 1.5rem; margin-bottom: 20px; border-bottom: 1px solid #000; padding-bottom: 10px; }" << "\r\n";
	ss << ".code { font-weight: bold; font-size: 1.2rem; }" << "\r\n";
	ss << ".footer { margin-top: 30px; font-size: 0.8rem; border-top: 1px solid #000; pt: 10px; }" << "\r\n";
	ss << "</style></head>" << "\r\n";
	ss << "<body>" << "\r\n";
	ss << "<div class='container'>" << "\r\n";
	ss << "<h1>Error Response</h1>" << "\r\n";
	ss << "<p><span class='code'>Error code:</span> " << status << "</p>" << "\r\n";
	ss << "<p><span class='code'>Message:</span> " << reason << "</p>" << "\r\n";
	ss << "<p><span class='code'>Explanation:</span> HTTP Status " << status << " - The server encountered an issue processing your request.</p>" << "\r\n";
	ss << "<div class='footer'>Webserv (42 Madrid)</div>" << "\r\n";
	ss << "</div>" << "\r\n";
	ss << "</body>" << "\r\n";
	ss << "</html>";
	return ss.str();
}

ErrorAction::ErrorAction(const HttpError &err): 
	Action(err.getServerConfig(), err.getLocationConfig()), 
	_status(err.getStatus()), 
	_statusMessage(err.getStatusMessage()),
	_version(err.getVersion()), _keep_alive(err.getKeepAlive())
{}

// Función que resuelve la ruta de la página de error según la jerarquía
std::string ErrorAction::_findErrorPagePath(int status, std::string &outRoot) const {
	// 1. Intentar en Location si existe
	if (_location != NULL) {
		const std::map<int, std::string> &locErrors = _location->getErrorPages();
		std::map<int, std::string>::const_iterator it = locErrors.find(static_cast<int>(_status));
		if (it != locErrors.end()) { //match
			outRoot = _location->getRoot();
			return it->second;
		}
	}
	
	//fallback to serverconfig
	const std::map<int, std::string> &srvErrors = _config->getErrorPages();
	std::map<int, std::string>::const_iterator it = srvErrors.find(status);
	if (it != srvErrors.end()) {
		outRoot = _config->getRoot();
		return it->second;
	}

	return ""; //not found
}

Response ErrorAction::exec() {
	if (_config == NULL) { //return fallback error response
		Response resp(_status, _statusMessage, generateDynamicErrorBody(_status, _statusMessage));
		resp.setVersion(_version);
		resp.setKeepAlive(_keep_alive);
		return resp;
	}

	std::string rootPath = "";
	std::string path = _findErrorPagePath(_status, rootPath);

	if (path.size() > 0) { //path found, try to resolve error page
		if (path[0] == '/') //if started with slash, concatenate to config root path, otherwise treat as local path
			path = Action::pathConcatenate(rootPath, path);

		struct stat filestat;
		if (stat(path.c_str(), &filestat) == 0) {
			if (S_ISREG(filestat.st_mode)) {
				std::ifstream infile(path.c_str()); //todo stress testing with larger files
    				if (infile) {
						std::ostringstream buffer;
    					buffer << infile.rdbuf(); //todo chunked buffering for large files?
						Response resp(_status, _statusMessage, buffer.str());
						resp.setVersion(_version);
						resp.setKeepAlive(_keep_alive);
						return resp;
    				}
			}
		}
	}

	//if not resolved, return generic response
    Response resp(_status, _statusMessage, generateDynamicErrorBody(_status, _statusMessage));
	resp.setVersion(_version);
	resp.setKeepAlive(_keep_alive);
	return resp;
}
