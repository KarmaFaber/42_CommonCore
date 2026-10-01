#include "ConfigValidatorData.hpp"

/******************************************************************************/
/*							PRIVATE FUNCTIONS								  */
/******************************************************************************/
void	ConfigValidatorData::checkLocations(const ServerConfig& server)
{
	const std::vector<LocationConfig>& locations = server.getLocations();

	if (locations.empty())
		throw ConfigException("Logic Error: Server block is missing"
							" 'location' directives. At least"
							" one location (e.g., '/') is required.");
	for (size_t i = 0; i < locations.size(); ++i)
	{
		const LocationConfig& loc = locations[i];

		checkCgiConsistency(loc);
		checkReturnLogic(loc);
	}
}

void ConfigValidatorData::checkCgiConsistency(const LocationConfig& loc)
{
	const std::map<std::string, std::string>& cgis = loc.getCgis();

	if (cgis.empty())
		return;
	for (std::map<std::string, std::string>::const_iterator it = cgis.begin(); it != cgis.end(); ++it)
	{
		if (it->second.empty())
		{
			throw ConfigException("Logic Error: Location defines CGI extension '" + 
								  it->first + "' but missing 'cgi_path'.");
		}
	}
}

void	ConfigValidatorData::checkReturnLogic(const LocationConfig& loc)
{
	const std::pair<int, std::string>& ret = loc.getReturnUrl();
	
	if (ret.first == 0)
		return;
	if (loc.getPathMatch() == ret.second)
	{
		throw ConfigException("Logic Error: Infinite redirect loop"
							 " detected. Location '" + loc.getPathMatch()
							 + "' returns to itself.");
	}
}
