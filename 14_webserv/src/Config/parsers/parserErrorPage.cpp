#include "ConfigParser.hpp"

/******************************************************************************/
/*							PRIVATE FUNCTIONS								  */
/******************************************************************************/
void	ConfigParser::parseErrorPage(ServerConfig& currentServer,
										std::string::iterator& it)
{
	std::vector<std::string> tokens = getMultiToken(it);
	if (tokens.size() < 2)
		throw (ConfigException("Syntax Error: error_page directive"
								" needs at least one code and a path."));
	std::string uri = tokens.back();
	checkUri(uri);
	for (size_t i = 0; i < tokens.size() - 1; i++)
	{
		std::string codeStr = tokens[i];
		for (size_t j = 0; j < codeStr.length(); j++)
		{
			if (!std::isdigit(codeStr[j]))
				throw (ConfigException("Syntax Error: error_page "
										"code must be numeric: " + codeStr));
		}
		int code = std::atoi(codeStr.c_str());
		if (code < 300 || code > 599)
			throw (ConfigException("Syntax Error: Invalid HTTP status code "
				"in error_page (must be between 300 and 599): " + codeStr));
		currentServer.addErrorPage(code, uri);
	}
}

void	ConfigParser::checkUri(std::string uri)
{
	for (size_t i = 0; i < uri.length(); i++)
	{
		if (!isValidPathChar(uri[i]))
		{
			throw (ConfigException("Syntax Error: Invalid character"
									" in error_page path: " + uri));
		}
	}
	if (uri[0] != '/')
	{
		throw (ConfigException("Syntax Error: error_page path must"
								" start with '/': " + uri));
	}
}
