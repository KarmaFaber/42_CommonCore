#include "LocationConfig.hpp"

LocationConfig::LocationConfig()
{
	_path_match = "";
	_root = "";
	_index.clear();
	_autoindex = -1;
	_cgis.clear();
	_upload_path = "";
	_client_max_body_size = 0;
	_return_url = std::make_pair(0, "");
	_allowed_methods.clear();
	_loc_error_pages.clear();
}

LocationConfig::~LocationConfig() {}

/******************************************************************************/
/*								GETTERS										  */
/******************************************************************************/
std::string	LocationConfig::getPathMatch() const
{
	return (_path_match);
}

std::string	LocationConfig::getRoot() const
{
	return (_root);
}

const std::vector<std::string>&	LocationConfig::getIndex() const
{
	return (_index);
}

std::vector<std::string>	LocationConfig::getAllowedMethods() const
{
	return (_allowed_methods);
}

bool	LocationConfig::isMethodAllowed(const std::string &method_str) const {
	for (std::vector<std::string>::const_iterator it = _allowed_methods.begin(); it < _allowed_methods.end(); it++) {
		if (*it == method_str)
			return true;
	}
	return (false);
}

const std::map<std::string, std::string>& LocationConfig::getCgis() const
{
	return _cgis;
}

size_t	LocationConfig::getClientMaxBodySize() const
{
	return (_client_max_body_size);
}

int	LocationConfig::getAutoindex() const
{
	return (_autoindex);
}

std::string	LocationConfig::getUploadPath() const
{
	return (_upload_path);
}

const std::pair<int, std::string>&	LocationConfig::getReturnUrl() const
{
	return (_return_url);
}

const std::map<int, std::string>& LocationConfig::getErrorPages() const
{
	return _loc_error_pages;
}

/******************************************************************************/
/*								SETTERS										  */
/******************************************************************************/
void	LocationConfig::setPathMatch(const std::string& path)
{
	_path_match = path;
}
void	LocationConfig::setRoot(const std::string& root)
{
	_root = root;
}
void	LocationConfig::addIndex(const std::string& index)
{
	_index.push_back(index);
}
void	LocationConfig::setAllowedMethods(const std::vector<std::string>& methods)
{
	_allowed_methods = methods;
}
void	LocationConfig::addAllowedMethod(const std::string& method)
{
	_allowed_methods.push_back(method);
}

void	LocationConfig::addCgi(const std::string& ext, const std::string& path)
{
	_cgis[ext] = path;
}

void	LocationConfig::setClientMaxBodySize(size_t size)
{
	_client_max_body_size = size;
}

void	LocationConfig::setAutoindex(int autoindex)
{
	_autoindex = autoindex;
}
void	LocationConfig::setUploadPath(const std::string& upload_path)
{
	_upload_path = upload_path;
}
void	LocationConfig::setReturnUrl(int code, const std::string& url)
{
	_return_url = std::make_pair(code, url);
}

void LocationConfig::addLocErrorPage(int code, const std::string& path)
{
	_loc_error_pages[code] = path;
}

/******************************************************************************/
/*								PRINTER										  */
/******************************************************************************/
std::string	LocationConfig::toStringPrint() const
{
	std::stringstream ss;
	
	ss << "\t\t|-> Path Match: " << _path_match << "\n";
	ss << "\t\t|   Root: " << _root << "\n";

	// INDEX
	ss <<  "\t\t|   Index: ";
	for (size_t i = 0; i < _index.size(); ++i) {
		ss << _index[i] << (i < _index.size() - 1 ? " " : "");
	}
	ss << "\n";
	
	// ALLOWED METHODS
	ss <<  "\t\t|   Allowed Methods: ";
	for (size_t i = 0; i < _allowed_methods.size(); ++i) {
		ss << _allowed_methods[i];
		if (i < _allowed_methods.size() - 1)
			ss << ", ";
	}
	ss << "\n";
	
	// CGI MAPPINGS
	ss << "\t\t|   CGI Mappings: extension/path:\n";
	if (_cgis.empty()) {
		ss << "\t\t|     (None)\n";
	} else {
		for (std::map<std::string, std::string>::const_iterator it = _cgis.begin(); it != _cgis.end(); ++it) {
			ss << "\t\t|     " << it->first << " -> " << it->second << "\n";
		}
	}

	// LOCATION ERROR PAGES
	ss << "\t\t|   Location Error Pages:\n";
	if (_loc_error_pages.empty()) {
		ss << "\t\t|     (None)\n";
	} else {
		for (std::map<int, std::string>::const_iterator it = _loc_error_pages.begin(); it != _loc_error_pages.end(); ++it) {
			ss << "\t\t|     Code " << it->first << " -> " << it->second << "\n";
		}
	}

	// OTHER DIRECTIVES
	ss <<  "\t\t|   Autoindex: " << (_autoindex ? "true" : "false") << "\n";
	ss <<  "\t\t|   Upload Path: "  << (_upload_path.empty() ? "(None)" : _upload_path) << "\n";
	ss <<  "\t\t|   Max Body Size: "  << _client_max_body_size << " bytes\n";
	
	// RETURN URL
	ss << "\t\t|   Return Url: ";
	if (_return_url.first != 0) {
		ss << "Code " << _return_url.first << " -> " << _return_url.second;
	} else {
		ss << "(None)";
	}
	ss << "\n";
	return ss.str();
}
