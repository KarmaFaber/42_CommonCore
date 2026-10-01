#include "ConfigParser.hpp"

/******************************************************************************/
/*							PRIVATE FUNCTIONS								  */
/******************************************************************************/
void	ConfigParser::skipWhitespaceAndComments(std::string::iterator& it)
{
	std::string::iterator end;

	end = _file_content.end();
	while (it != end)
	{
		if (std::isspace(*it))
		{
			it++;
		}
		else if (*it == '#')
		{
			while (it != end && *it != '\n')
			{
				it++;
			}
		}
		else
		{
			break;
		}
	}
}
