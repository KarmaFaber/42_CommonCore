#pragma once

#include "ServerConfig.hpp"
#include "LocationConfig.hpp"
#include "ConfigException.hpp"
#include <vector>
#include <map>
#include <set>
#include <iostream>
#include <unistd.h>

class ConfigValidatorData
{
	private:
		static void	checkServerRoot(const ServerConfig& server);
		static void	checkDuplicateServers(const std::vector<ServerConfig>& servers);
		static void	checkErrorPages(const ServerConfig& server);
		static void	checkLocations(const ServerConfig& server);
		static void	checkCgiConsistency(const LocationConfig& loc);
		static void	checkReturnLogic(const LocationConfig& loc);
	public:
		static void	validateData (const std::vector<ServerConfig>& servers);
};
