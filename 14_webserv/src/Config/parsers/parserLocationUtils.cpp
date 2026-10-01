#include "ConfigParser.hpp"

/******************************************************************************/
/*							PUBLIC FUNCTIONS								  */
/******************************************************************************/
void	ConfigParser::parseLocationIndex(LocationConfig& loc,
											std::string::iterator& it)
{
	std::vector<std::string> indexes;

	indexes = getMultiToken(it);
	for (size_t i = 0; i < indexes.size(); i++)
	{
		std::string& index = indexes[i];
		for (size_t j = 0; j < index.length(); j++)
		{
			if (index[j] == ',')
				throw (ConfigException("Syntax Error: Invalid character"
										" ',' in index (Location)."));
			
			if (!isValidPathChar(index[j]))
				throw (ConfigException("Syntax Error: Invalid character"
										" in index (Location): " + index));
		}
		loc.addIndex(index);
	}
}

void	ConfigParser::parseAllowedMethods(LocationConfig& location,
											std::string::iterator& it)
{
	std::vector<std::string> methods;
	std::vector<std::string> validMethods;

	methods = getMultiToken(it);
	for (size_t i = 0; i < methods.size(); i++)
	{
		std::string m = methods[i];
		if (m != "GET" && m != "POST" && m != "DELETE")
			throw (ConfigException("Syntax Error: Invalid HTTP method: " + m));
		validMethods.push_back(m);
	}
	location.setAllowedMethods(validMethods);
}

void ConfigParser::parseCgiPass(LocationConfig& loc, std::string::iterator& it)
{
	std::vector<std::string> tokens = getMultiToken(it);

	if (tokens.size() != 2)
		throw ConfigException("Syntax Error: cgi_pass requires exactly two arguments: .extension path");
	std::string ext = tokens[0];
	std::string path = tokens[1];
	if (ext.length() < 2 || ext[0] != '.')
		throw ConfigException("Syntax Error: Invalid CGI extension '" + ext + "'. Must start with '.' followed by characters.");
	
	for (size_t i = 1; i < ext.length(); i++) {
		if (!std::isalnum(ext[i]))
			throw ConfigException("Syntax Error: Invalid character in CGI extension: " + ext);
	}
	if (path == ".")
		throw ConfigException("Syntax Error: CGI path cannot be '.'");
	for (size_t i = 0; i < path.length(); i++) {
		if (!isValidPathChar(path[i]))
			throw ConfigException("Syntax Error: Invalid character in cgi_path: " + path);
	}
	if (isKeyword(path))
		 throw ConfigException("Syntax Error: CGI path cannot be a configuration keyword: " + path);

	loc.addCgi(ext, path);
}
