#include "ServerConfig.hpp"

ServerConfig::ServerConfig()
{
	_host_ip = "0.0.0.0";
	_port = 80;
	_server_names.clear();
	_client_max_body_size = (1 * 1024 * 1024);
	_root = "";
	_index.clear();
	_error_pages.clear();
	_autoindex = -1;
	_upload_path = "";
	_allowed_methods.clear();
	_return_url = std::make_pair(0, "");
}

ServerConfig::~ServerConfig() {}

/******************************************************************************/
/*								GETTERS										  */
/******************************************************************************/
std::vector<LocationConfig>&	ServerConfig::getLocationsRef()
{
	return (_locations);
}

const std::vector<std::string>&	ServerConfig::getServerNames() const
{
	return (_server_names);
}

const std::vector<std::string>&	ServerConfig::getIndex() const
{
	return (_index);
}

const std::map<int, std::string>&	ServerConfig::getErrorPages() const
{
	return (_error_pages);
}

const std::vector<LocationConfig>&	ServerConfig::getLocations() const
{
	return (_locations);
}

std::string	ServerConfig::getHost() const
{
	return (_host_ip);
}
int	ServerConfig::getPort() const
{
	return (_port);
}

size_t	ServerConfig::getClientMaxBodySize() const
{
	return (_client_max_body_size);
}

std::string	ServerConfig::getRoot() const
{
	return (_root);
}

int	ServerConfig::getAutoindex() const
{
	return (_autoindex);
}

std::string	ServerConfig::getUploadPath() const
{
	return (_upload_path);
}

const std::pair<int, std::string>&	ServerConfig::getReturnUrl() const
{
	return (_return_url);
}

std::vector<std::string>	ServerConfig::getAllowedMethods() const
{
	return (_allowed_methods);
}

bool	ServerConfig::isMethodAllowed(const std::string &method_str) const {
	for (std::vector<std::string>::const_iterator it = _allowed_methods.begin(); it < _allowed_methods.end(); it++) {
		if (*it == method_str)
			return true;
	}
	return (false);
}

/******************************************************************************/
/*								SETTERS										  */
/******************************************************************************/
void	ServerConfig::setHost(const std::string& host)
{
	_host_ip = host;
}
void	ServerConfig::setPort(int port)
{
	_port = port;
}
void	ServerConfig::setClientMaxBodySize(size_t size)
{
	_client_max_body_size = size;
}
void	ServerConfig::setRoot(const std::string& root)
{
	_root = root;
}

void	ServerConfig::setAutoindex(int autoindex)
{
	_autoindex = autoindex;
}

void	ServerConfig::setUploadPath(const std::string& path)
{
	_upload_path = path;
}

void	ServerConfig::setReturnUrl(int code, const std::string& url)
{
	_return_url = std::make_pair(code, url);
}

void	ServerConfig::setAllowedMethods(const std::vector<std::string>& methods)
{
	_allowed_methods = methods;
}

void	ServerConfig::addServerName(const std::string& name)
{
	_server_names.push_back(name);
}
void	ServerConfig::addIndex(const std::string& index)
{
	_index.push_back(index);
}

void	ServerConfig::addErrorPage(int code, const std::string& path)
{
	_error_pages[code] = path;
}

void	ServerConfig::addAllowedMethod(const std::string& method)
{
	_allowed_methods.push_back(method);
}
void	ServerConfig::addLocation(const LocationConfig& location)
{
	_locations.push_back(location);
}

/******************************************************************************/
/*								PRINTER										  */
/******************************************************************************/
std::string	ServerConfig::toStringPrint() const
{
	std::stringstream ss;

	ss << "\n======================================================\n";
	ss << "   *** SERVER CONFIGURATION BLOCK *** \n";
	ss << "======================================================\n";

	// 1. Login/Identification Information
	ss << "[ Connection & Identity ]\n";
	ss << "Host IP: " << _host_ip << "\n";
	ss  << "Port: " << _port << "\n";
	
	// Server Names
	ss << "Server Names: ";
	for (size_t i = 0; i < _server_names.size(); ++i) {
		ss << _server_names[i];
		if (i < _server_names.size() - 1)
			ss << ", " ;
	}
	ss << "\n\n";

	// 2. Global Directives
	ss << "[ Global Directives ]\n";
	ss  << "Max Body Size: " << _client_max_body_size << " bytes\n";
	ss << "Root: " << _root << "\n";
	
	//INDEX
	ss << "Index: ";
	for (size_t i = 0; i < _index.size(); ++i) {
		ss << _index[i];
		if (i < _index.size() - 1)
			ss << ", ";
	}
	ss << "\n";
	ss <<  "Autoindex: " << (_autoindex ? "true" : "false") << "\n";
	ss <<  "Upload path: " << _upload_path << "\n";

	//Allowed Methods
	ss << "Allowed Methods: ";
	for (size_t i = 0; i < _allowed_methods.size(); ++i) {
		ss << _allowed_methods[i];
		if (i < _allowed_methods.size() - 1)
			ss << ", ";
	}
	ss << "\n";

	//RETURN URL
	ss << "Return Url: ";
	if (_return_url.first != 0)
	{
		ss << "Code " << _return_url.first << " -> " << _return_url.second;
	}
	else
	{
		ss << "(None)";
	}
	ss << "\n";

	// Error Pages
	ss << "Error Pages:\n";
	for (std::map<int, std::string>::const_iterator it = _error_pages.begin(); it != _error_pages.end(); ++it) {
		ss << "  - Code " << it->first << " -> Path: " << it->second << "\n";
	}
	ss << "\n";

	// 3. Container for Specific Routes (Locations)
	ss << "[ Location Blocks (" << _locations.size() << " total) ] \n";
	if (_locations.empty()) {
		ss << "  (No locations defined)\n";
	} else {
		for (size_t i = 0; i < _locations.size(); ++i) {
			ss << "\t-> LOCATION " << i + 1 << " {\n";
			ss << _locations[i].toStringPrint(); 
			ss << "\t}\n";
		}
	}
	ss << "======================================================\n";
	return ss.str();
}
