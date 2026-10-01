#include "ConfigParser.hpp"

template <typename T>
void ConfigParser::parseAutoindex(T& config, std::string::iterator& it)
{
	std::string value;

	value = getNextToken(it);
	if (value == "on")
		config.setAutoindex(1);
	else if (value == "off")
		config.setAutoindex(0);
	else
		throw (ConfigException("Syntax Error: autoindex must be 'on' or 'off'."));
}

template <typename T>
void ConfigParser::parseReturn(T& config, std::string::iterator& it)
{
	std::vector<std::string> args = getMultiToken(it);
	if (args.empty())
		throw (ConfigException("Syntax Error: 'return' directive cannot be empty."));
	if (args.size() > 2)
		throw (ConfigException("Syntax Error: 'return' accepts at most 2 arguments (code + url)."));
	int code = 302;
	std::string url;
	if (args.size() == 2)
	{
		std::string codeStr = args[0];
		url = args[1];
		for (size_t i = 0; i < codeStr.length(); i++)
		{
			if (!std::isdigit(codeStr[i]))
				throw (ConfigException("Syntax Error: return code must be numeric."));
		}
		code = std::atoi(codeStr.c_str());
		if (code < 100 || code > 599)
			 throw (ConfigException("Syntax Error: return code out of valid HTTP range."));
	}
	else
		url = args[0];
	if (url.empty())
		throw (ConfigException("Syntax Error: return URL cannot be empty."));
	config.setReturnUrl(code, url);
}

template <typename T>
void ConfigParser::parseBodySize(T& config, std::string::iterator& it)
{
	std::string temp_body_size = getNextToken(it);
	parseBodySizeValue(config, temp_body_size);
}

template <typename T>
void ConfigParser::parseBodySizeValue(T& config, std::string token)
{
	std::string num_part;
	char suffix = extractSuffix(token, num_part); 
	errno = 0;
	char* end;
	unsigned long number = std::strtoul(num_part.c_str(), &end, 10);
	if (errno == ERANGE)
		throw (ConfigException("Syntax Error: Number too large in client_max_body_size"));
	if (suffix == '\0')
	{
		if (number == 0)
		{
			config.setClientMaxBodySize(0);
			return;
		}
		throw (ConfigException("Syntax Error: client_max_body_size requires a unit (k, m, g) unless value is 0."));
	}
	size_t multiplier = getMultiplier(suffix);
	size_t max_limit = std::numeric_limits<size_t>::max();
	if (number > max_limit / multiplier)
		throw (ConfigException("Syntax Error: client_max_body_size is too large (overflow)"));
	config.setClientMaxBodySize(number * multiplier);
}

template <typename T>
void ConfigParser::parseRoot(T& config, std::string::iterator& it)
{
	std::string rootPath = getNextToken(it);

	for (size_t i = 0; i < rootPath.length(); i++)
	{
		if (rootPath[i] == ',')
			throw (ConfigException("Syntax Error: Invalid character ',' in root directive."));
		if (!isValidPathChar(rootPath[i]))
			throw (ConfigException("Syntax Error: Invalid character in root path: " + rootPath));
	}
	if (rootPath.find("..") != std::string::npos)
		 throw (ConfigException("Syntax Error: '..' is not allowed in root path for security."));

	config.setRoot(rootPath);
}

template <typename T>
void ConfigParser::parseAllowedMethods(T& config, std::string::iterator& it)
{
	std::vector<std::string> methods = getMultiToken(it);
	std::vector<std::string> validMethods;

	for (size_t i = 0; i < methods.size(); i++)
	{
		if (methods[i] != "GET" && methods[i] != "POST" && methods[i] != "DELETE")
			throw (ConfigException("Syntax Error: Invalid HTTP method: " + methods[i]));
		validMethods.push_back(methods[i]);
	}
	config.setAllowedMethods(validMethods);
}
