#include "ConfigParser.hpp"

/******************************************************************************/
/*							PRIVATE FUNCTIONS								  */
/******************************************************************************/
void	ConfigParser::parseVectorDirective(ServerConfig& conf,
		std::string::iterator& it, SetterFunc setter, std::string directiveName)
{
	std::vector<std::string> values = getMultiToken(it);
	for (size_t i = 0; i < values.size(); i++)
	{
		std::string& val = values[i];
		for (size_t j = 0; j < val.length(); j++)
		{
			if (val[j] == ',')
				throw (ConfigException("Syntax Error: Invalid character ',' in "
						+ directiveName));
			bool isValid = true;
			if (directiveName == "server_name")
			{
				isValid = isValidDomainChar(val[j]);
			}
			else if (directiveName == "index")
			{
				isValid = isValidPathChar(val[j]);
			}
			if (!isValid)
				throw (ConfigException("Syntax Error: Invalid character in "
						+ directiveName + ": " + val));
		}
		(conf.*setter)(val);
	}
}
