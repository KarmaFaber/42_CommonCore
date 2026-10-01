#include "ConfigParser.hpp"

/******************************************************************************/
/*							PRIVATE FUNCTIONS								  */
/******************************************************************************/
char	ConfigParser::extractSuffix(const std::string& token,
								std::string& num_part)
{
	char suffix;

	suffix = '\0';
	for (size_t i = 0; i < token.length(); i++)
	{
		if (std::isdigit(token[i]))
		{
			num_part += token[i];
		}
		else
		{
			if (i != token.length() - 1)
				throw (ConfigException("Syntax Error: Invalid format in"
						" client_max_body_size (suffix not at end): " + token));
			suffix = token[i];
			if (!isValidSuffix(suffix))
				 throw (ConfigException("Syntax Error: Invalid suffix"
						" in client_max_body_size: " + token));
		}
	}
	if (num_part.empty())
		throw (ConfigException("Syntax Error: Missing numeric value"
						" in client_max_body_size"));
	return (suffix);
}

size_t	ConfigParser::getMultiplier(char suffix)
{
	char lower;
	
	if (suffix == '\0')
		return (1);
	lower = std::tolower(suffix);
	if (lower == 'k')
		return (1024);
	if (lower == 'm')
		return (1024 * 1024);
	if (lower == 'g')
		return (1024 * 1024 * 1024);
	return (1);
}

bool	ConfigParser::isValidSuffix(char c)
{
	char lower;

	lower = std::tolower(c);
	if (lower == 'k' || lower == 'm' || lower == 'g')
		return (true);
	return (false);
}
