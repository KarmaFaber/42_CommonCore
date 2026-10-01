#include "ConfigParser.hpp"

/******************************************************************************/
/*						CONSTRUCTORS & DESTRUCTORS							  */
/******************************************************************************/
void ServerConfig::propagateErrorsToLocations()
{
	for (size_t i = 0; i < _locations.size(); ++i)
	{
		LocationConfig& loc = _locations[i];
		const std::map<int, std::string>& srvErrors = this->getErrorPages();
		for (std::map<int, std::string>::const_iterator it = srvErrors.begin(); it != srvErrors.end(); ++it)
		{
			if (loc.getErrorPages().find(it->first) == loc.getErrorPages().end())
			{
				loc.addLocErrorPage(it->first, it->second);
			}
		}
	}
}

ConfigParser::ConfigParser(const std::string& path)
	: _configFilePath(path),
	  _file_content(""),
	  _servers(),
	  _nb_server(0)
{
	initServerMap();
	_server_data = false;
	parseConfigFile(path);
	for (size_t i = 0; i < _servers.size(); ++i)
	{
		_servers[i].propagateErrorsToLocations();
	}
}

ConfigParser::~ConfigParser() {}

/******************************************************************************/
/*								GETTERS										  */
/******************************************************************************/
const std::vector<ServerConfig>&	ConfigParser::getServers() const
{ 
	return (_servers);
}

size_t	ConfigParser::getServNum (void) const
{
	return (_nb_server);
}

std::string	ConfigParser::getFileContent(void) const
{
	return (_file_content);
}

/******************************************************************************/
/*								PRINTER										  */
/******************************************************************************/

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v)
{
	os << "[";
	for (size_t i = 0; i < v.size(); ++i)
	{
		os << v[i];
		if (i != v.size() - 1)
			os << ", ";
	}
	os << "]";
	return os;
}

void	ConfigParser::printDebug() const
{
	std::cout << "\n**------------------------------***---***---***---***---------------------------------------**\n";
	std::cout << "\n========================================================\n";
	std::cout << "PRINTER: START OF CONFIGURATION PARSER SUMMARY\n";
	std::cout << "========================================================\n";
	std::cout << "File: " << _configFilePath << "\n";
	std::cout << "Total Servers Parsed: " << _nb_server << " / " << _servers.size() << "\n";
	std::cout << "--------------------------------------------------------\n";

	if (_servers.empty())
	{
		std::cout << "The server vector is empty!\n";
	}
	else
	{
		for (size_t i = 0; i < _servers.size(); ++i)
		{
			std::cout << ">>> SERVER BLOCK " << i + 1 << " <<<\n";
			std::cout << _servers[i].toStringPrint();
		}
	}
	std::cout << "========================================================\n";
	std::cout << "PRINTER: END OF CONFIGURATION PARSER SUMMARY\n";
	std::cout << "========================================================\n\n";
}
