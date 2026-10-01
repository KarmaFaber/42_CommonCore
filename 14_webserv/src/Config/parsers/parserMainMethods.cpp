#include "ConfigParser.hpp"
#include <fstream>

/******************************************************************************/
/*							PUBLIC FUNCTIONS								  */
/******************************************************************************/
void	ConfigParser::parseConfigFile(const std::string& path)
{
	std::ifstream conf_file(path.c_str());

	if (!conf_file.is_open())
		throw (ConfigException("Could not open configuration file."));
	std::stringstream buffer;
	buffer << conf_file.rdbuf();
	_file_content = buffer.str();
	conf_file.close();
	if (_file_content.empty())
		throw (ConfigException("Configuration file is empty."));
	parseFileContentVar();
	if (_servers.empty())
		throw (ConfigException("Syntax error: No 'server' block in configuration."));
	finalizeConfig();
	ConfigValidatorData::validateData(_servers);
}

void	ConfigParser::parseFileContentVar(void)
{
	std::string::iterator it = _file_content.begin();
	while (it != _file_content.end())
	{
		skipWhitespaceAndComments(it);
		if (*it == '{' || *it == '}')
			throw (ConfigException("Syntax error: unexpected token '" + std::string(1, *it) + "' outside of server block."));
		if (it == _file_content.end() && !_server_data)
			throw (ConfigException("Syntax error: the file only contains comments or spaces."));
		std::string::iterator start = it;
		while (it != _file_content.end() && !std::isspace(*it) && *it != '{' && *it != ';')
			++it;
		std::string word(start, it);
		if (word == "server")
		{
			parseServerBlock(it);
			_server_data = true;
			_nb_server++;
			skipWhitespaceAndComments(it);
		}
		else
			throw (ConfigException("Syntax error: unexpected token '" + word + "' outside of server block."));
	}
}

void	ConfigParser::parseServerBlock(std::string::iterator& it)
{
	skipWhitespaceAndComments(it);
	if (it == _file_content.end() || *it != '{')
		throw (ConfigException("Syntax error: Expected '{' after 'server' directive."));
	it++;

	ServerConfig currentServer; 
	while (it != _file_content.end())
	{
		skipWhitespaceAndComments(it);
		if (it == _file_content.end())
			 throw (ConfigException("Syntax error: Missing closing '}' for server block."));
		if (*it == '}')
		{
			it++;
			_servers.push_back(currentServer);
			return;
		}
		std::string directive;
		while (it != _file_content.end() && !std::isspace(*it) && *it != ';' && *it != '{' && *it != '}')
		{
			directive += *it;
			it++;
		}
		if (_serverDirectives.count(directive))
		{
			ServerParserFunc func = _serverDirectives[directive];
			(this->*func)(currentServer, it);
		}
		else if (directive == "try_files") 
			 throw (ConfigException("Syntax error: Directive '" + directive + "' not allowed in server block (or not implemented)."));
		else
			throw (ConfigException("Syntax error: Unknown directive '" + directive + "' inside server block."));
	}
}

void	ConfigParser::finalizeConfig()
{
	for (size_t i = 0; i < _servers.size(); ++i)
	{
		ServerConfig& server = _servers[i];
		if (server.getIndex().empty())
			server.addIndex("index.html");
		if (server.getAutoindex() == -1)
			server.setAutoindex(0);
		if (server.getAllowedMethods().empty())
			server.addAllowedMethod("GET");
		if (server.getUploadPath().empty())
			server.setUploadPath("/uploads/");
		std::vector<LocationConfig>& locations = server.getLocationsRef(); 
		for (size_t j = 0; j < locations.size(); ++j)
		{
			LocationConfig& loc = locations[j];
			if (loc.getRoot().empty() && !server.getRoot().empty())
				loc.setRoot(server.getRoot());
			if (loc.getIndex().empty())
			{
				const std::vector<std::string>& serverIndex = server.getIndex();
				for (size_t k = 0; k < serverIndex.size(); k++)
					loc.addIndex(serverIndex[k]);
			}
			if (loc.getAllowedMethods().empty())
				loc.addAllowedMethod("GET");
			if (loc.getAutoindex() == -1)
				loc.setAutoindex(server.getAutoindex()); 
			if (loc.getReturnUrl().first == 0 && server.getReturnUrl().first != 0)
				loc.setReturnUrl(server.getReturnUrl().first, server.getReturnUrl().second);
			if (loc.getClientMaxBodySize() == 0) 
				loc.setClientMaxBodySize(server.getClientMaxBodySize());
			if (loc.getUploadPath().empty())
			{
				std::string root = loc.getRoot();

				if (!server.getUploadPath().empty())
					loc.setUploadPath("/uploads/");
			}
		}
	}
}
