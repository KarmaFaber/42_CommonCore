#include "ConfigParser.hpp"

/******************************************************************************/
/*							PUBLIC FUNCTIONS								  */
/******************************************************************************/

void	ConfigParser::parseLocationBlock(ServerConfig& currentServer,
											std::string::iterator& it)
{
	LocationConfig newLocation;
	parseLocationPath(newLocation, it);
	parseLocationBody(newLocation, it);
	currentServer.addLocation(newLocation);
}

void	ConfigParser::parseLocationPath(LocationConfig& loc,
											std::string::iterator& it)
{
	skipWhitespaceAndComments(it);
	std::string path;
	while (it != _file_content.end() && !std::isspace(*it) && *it != '{')
	{
		path += *it;
		it++;
	}
	if (path.empty())
		throw (ConfigException("Syntax Error: Location block is missing"
								" a path."));
	if (path[0] != '/')
		throw (ConfigException("Syntax Error: Location path must start"
								" with '/': " + path));
	loc.setPathMatch(path);
	skipWhitespaceAndComments(it);
	if (it == _file_content.end() || *it != '{')
		throw (ConfigException("Syntax Error: Missing '{' in location"
								" block."));
	it++;
}

void	ConfigParser::parseLocationBody(LocationConfig& loc,
											std::string::iterator& it)
{
	while (it != _file_content.end())
	{
		skipWhitespaceAndComments(it);
		if (it != _file_content.end() && *it == '}')
		{
			it++;
			return;
		}
		std::string directive;
		while (it != _file_content.end() && !std::isspace(*it) &&
				*it != ';' && *it != '}')
		{
			directive += *it;
			it++;
		}
		parseLocationDirective(loc, directive, it);
	}
	throw (ConfigException("Syntax Error: Unexpected end of file "
							"inside location block."));
}

void	ConfigParser::parseLocationDirective (LocationConfig& loc,
					std::string& directive, std::string::iterator& it)
{
	if (directive == "root")
		parseRoot(loc, it);
	else if (directive == "index")
		parseLocationIndex(loc, it);
	else if (directive == "autoindex")
		parseAutoindex(loc, it);
	else if (directive == "allow_methods" || directive ==  "methods") 
		parseAllowedMethods(loc, it);
	else if (directive == "return")
		parseReturn(loc, it);
	else if (directive == "cgi_pass")
		parseCgiPass(loc, it);
	else if (directive == "client_max_body_size")
		parseBodySize(loc, it);
	else if (!directive.empty())
		throw (ConfigException("Syntax Error: Unknown directive inside"
								" location: " + directive));
}
