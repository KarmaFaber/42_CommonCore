#include "ConfigParser.hpp"

/******************************************************************************/
/*							PRIVATE FUNCTIONS								  */
/******************************************************************************/
void	ConfigParser::parseListen(ServerConfig& currentServer, std::string::iterator& it)
{
	std::string temp_listen = getNextToken(it);
	size_t	dob = temp_listen.find(':');
	if (dob == std::string::npos)
	{
		size_t	point = temp_listen.find('.');
		if (point== std::string::npos)
		{
			if (temp_listen == "localhost")
			{
				parseHost(temp_listen, currentServer);
				currentServer.setPort(80);
			}
			else
			{
				parsePort(temp_listen, currentServer);
				currentServer.setHost("0.0.0.0");
			}
		}
		else
		{
			parseHost(temp_listen, currentServer);
			currentServer.setPort(80);
		}
	}
	else
		splitHostPort(temp_listen, currentServer);
}

void	ConfigParser::parsePort(std::string token, ServerConfig& currentServer)
{
	for (size_t i = 0; i < token.length(); i++)
	{
		if (!isdigit(token[i]))
		{
			throw (ConfigException("Invalid value: Port contains non-numeric characters."));
		}
	}
	int temp_port = atoi(token.c_str());
	if (temp_port < 0 || temp_port > 65535)
		throw (ConfigException("Invalid value: Port number out of range (0-65535)."));
	currentServer.setPort(temp_port);
}

void	ConfigParser::parseHost(std::string token, ServerConfig& currentServer)
{
	if (token == "localhost")
	{
		currentServer.setHost("127.0.0.1");
		return;
	}
	int dots = 0;
	for (size_t i = 0; i < token.length(); i++)
	{
		if (token[i] == '.')
			dots++;
	}
	if (dots != 3)
		throw (ConfigException("Invalid Host format: Must contain exactly 3 dots (x.x.x.x)"));
	std::stringstream stream_str(token);
	std::string octet;
	int count = 0;
	validateOctet(stream_str, octet, count);
	if (count != 4)
		throw (ConfigException("Invalid Host format: Must contain 4 octets"));
	currentServer.setHost(token);
}

void	ConfigParser::validateOctet(std::stringstream& stream_str_var, std::string& octet_var, int& count_var)
{
	while (std::getline(stream_str_var, octet_var, '.'))
	{
		if (octet_var.empty())
			throw (ConfigException("Invalid Host format: Empty octet"));
		for (size_t i = 0; i < octet_var.length(); i++)
		{
			if (!isdigit(octet_var[i]))
				throw (ConfigException("Invalid Host format: Non-numeric character"));
		}
		int num = atoi(octet_var.c_str());
		if (num < 0 || num > 255)
			throw (ConfigException("Invalid Host format: Octet out of range (0-255)"));
		count_var++;
	}
}

void	ConfigParser::splitHostPort(std::string token, ServerConfig& currentServer)
{
	size_t pos = token.find(':');
	std::string temp_host = token.substr(0, pos);
	std::string temp_port = token.substr(pos + 1);
	parseHost(temp_host, currentServer);
	parsePort(temp_port, currentServer);
}
