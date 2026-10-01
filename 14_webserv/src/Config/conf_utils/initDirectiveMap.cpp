#include "ConfigParser.hpp"

/******************************************************************************/
/*							PRIVATE FUNCTIONS								  */
/******************************************************************************/
void	ConfigParser::initServerMap()
{
	_serverDirectives["listen"] = &ConfigParser::parseListen;
	_serverDirectives["root"] = &ConfigParser::parseRootWrapper;
	_serverDirectives["client_max_body_size"] = &ConfigParser::parseBodySize;
	_serverDirectives["error_page"] = &ConfigParser::parseErrorPage;
	_serverDirectives["location"] = &ConfigParser::parseLocationBlock;
	_serverDirectives["autoindex"] = &ConfigParser::parseAutoindexWrapper;
	_serverDirectives["return"] = &ConfigParser::parseReturnWrapper;
	_serverDirectives["server_name"] = &ConfigParser::parseServerNameWrapper;
	_serverDirectives["index"] = &ConfigParser::parseIndexWrapper;
	_serverDirectives["allow_methods"] = &ConfigParser::parseAllowedMethods;
}
