#include "ConfigParser.hpp"

/******************************************************************************/
/*							PRIVATE FUNCTIONS								  */
/******************************************************************************/
std::string	ConfigParser::getNextToken(std::string::iterator& it)
{
	std::string temp_token;
	
	skipWhitespaceAndComments(it);
	if (it == _file_content.end() || *it == ';') 
		throw (ConfigException("Syntax Error: Directive is missing a value"));
	while (it != _file_content.end() && *it != ';' && !std::isspace(*it))
	{
		temp_token += *it;
		it++;
	}
	skipWhitespaceAndComments(it);
	if (it == _file_content.end() || *it != ';')
		throw (ConfigException("Syntax Error: Missing semicolon in token"));
	it++;
	return (temp_token);
}
