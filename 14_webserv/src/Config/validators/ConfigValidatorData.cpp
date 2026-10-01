#include "ConfigValidatorData.hpp"

/******************************************************************************/
/*							PUBLIC FUNCTIONS								  */
/******************************************************************************/
void	ConfigValidatorData::validateData (const std::vector<ServerConfig>& servers)
{
	if (servers.empty())
		throw ConfigException("Global Error: No servers configured.");
	checkDuplicateServers(servers);
	for (size_t i = 0; i < servers.size(); ++i)
	{
		checkServerRoot(servers[i]);
		checkLocations(servers[i]);
		checkErrorPages(servers[i]);
	}
}
