#include "ConfigParser.hpp"

/******************************************************************************/
/*							PRIVATE FUNCTIONS								  */
/******************************************************************************/

std::vector<std::string>	ConfigParser::getMultiToken(std::string::iterator& it)
{
	std::vector<std::string> tokens;
	while (it != _file_content.end() && *it != ';')
	{
		skipWhitespaceAndComments(it);
		if (it == _file_content.end())
			throw (ConfigException("Syntax Error: Unexpected end of file inside directive."));
		if (*it == ';')
			break;
		if (*it == '{' || *it == '}')
			throw (ConfigException("Syntax Error: Missing semicolon in token"));
		std::string value;
		while (it != _file_content.end() && !std::isspace(*it) && *it != ';')
		{
			value += *it;
			it++;
		}
		if (isKeyword(value))
			 throw (ConfigException("Syntax Error: Missing semicolon before keyword '" + value + "'."));
		if (!value.empty())
			tokens.push_back(value);
	}
	if (tokens.empty())
		throw (ConfigException("Syntax Error: Directive is missing a value"));
	if (it == _file_content.end())
		throw (ConfigException("Syntax Error: Missing semicolon at end of directive."));
	it++;
	return (tokens);
}

bool	ConfigParser::isKeyword(const std::string& word)
{
	if (word == "listen" || word == "server_name" || word == "root" ||
		word == "index" || word == "error_page" || word == "location" ||
		word == "client_max_body_size" || word == "autoindex" ||
		word == "return" || word == "cgi_pass" ||
		word == "allowed_methods" )
	{
		return (true);
	}
	return (false);
}

bool	ConfigParser::isValidDomainChar(char c)
{
	if (std::isalnum(c) || c == '.' || c == '-' || c == '_' || c == '*')
		return (true);
	return (false);
}

bool	ConfigParser::isValidPathChar(char c)
{
	if (std::isalnum(c) || c == '.' || c == '-' || c == '_' || c == '/' || c == '+' || c == '~')
		return (true);
	return (false);
}
