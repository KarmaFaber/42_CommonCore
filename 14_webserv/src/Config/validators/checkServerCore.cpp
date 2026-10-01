#include "ConfigValidatorData.hpp"
#include <sstream>

/******************************************************************************/
/*							PRIVATE FUNCTIONS								  */
/******************************************************************************/
void	ConfigValidatorData::checkServerRoot(const ServerConfig& server)
{
	if (server.getRoot().empty())
		throw ConfigException("Logic Error: Server block missing"
								" mandatory 'root' directive.");
}

void	ConfigValidatorData::checkDuplicateServers(const std::vector<ServerConfig>& servers)
{
	std::map<std::string, std::set<std::string> > used_sockets;

	for (size_t i = 0; i < servers.size(); ++i)
	{
		std::stringstream ss;
		ss << servers[i].getHost() << ":" << servers[i].getPort();
		std::string socketKey = ss.str();
		std::vector<std::string> names = servers[i].getServerNames();
		if (names.empty()) 
			names.push_back("");
		for (size_t j = 0; j < names.size(); ++j)
		{
			std::string name = names[j];
			if (used_sockets[socketKey].count(name))
			{
				throw ConfigException("Logic Error: Duplicate server for " + socketKey + 
									 " with server_name '" + (name.empty() ? "(empty)" : name) + "'");
			}
			used_sockets[socketKey].insert(name);
		}
	}
}

void ConfigValidatorData::checkErrorPages(const ServerConfig& server)
{
	const std::map<int, std::string>& pages = server.getErrorPages();
	std::string root = server.getRoot();

	if (root.empty())
		return;
	std::map<int, std::string>::const_iterator it;
	for (it = pages.begin(); it != pages.end(); ++it)
	{
		int code = it->first;
		std::string uri = it->second;
		std::string fullPath;
		if (root[root.length() - 1] == '/' && uri[0] == '/')
			fullPath = root + uri.substr(1);
		else if (root[root.length() - 1] != '/' && uri[0] != '/')
			fullPath = root + "/" + uri;
		else
			fullPath = root + uri;
		if (access(fullPath.c_str(), R_OK) != 0)
		{
			std::cerr << "⚠️ Warning: Configured error_page for code " << code 
					<< " not found at: " << fullPath 
					<< ". Internal default page will be used instead." << std::endl;
		}
	}
}
