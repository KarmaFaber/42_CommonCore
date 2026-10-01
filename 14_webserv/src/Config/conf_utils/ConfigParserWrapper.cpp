#include "ConfigParser.hpp"

/******************************************************************************/
/*							PRIVATE FUNCTIONS								  */
/******************************************************************************/
void	ConfigParser::parseServerNameWrapper(ServerConfig& config, std::string::iterator& it)
{
	parseVectorDirective(config, it, &ServerConfig::addServerName, "server_name");
}

void	ConfigParser::parseIndexWrapper(ServerConfig& config, std::string::iterator& it)
{
	parseVectorDirective(config, it, &ServerConfig::addIndex, "index");
}

void	ConfigParser::parseReturnWrapper(ServerConfig& conf, std::string::iterator& it)
{
	parseReturn(conf, it);
}

void	ConfigParser::parseAutoindexWrapper(ServerConfig& conf, std::string::iterator& it)
{
	parseAutoindex(conf, it);
}

void	ConfigParser::parseRootWrapper(ServerConfig& config, std::string::iterator& it)
{
	parseRoot(config, it);
}

void ConfigParser::parseAllowedMethodsWrapper(ServerConfig& config, std::string::iterator& it)
{
	parseAllowedMethods(config, it);
}
