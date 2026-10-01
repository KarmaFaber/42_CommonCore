/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPNUtils.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 11:51:47 by mzolotar          #+#    #+#             */
/*   Updated: 2026/02/17 19:22:57 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

/******************************************************************************/
/*							PRIVATE METHODS									  */
/******************************************************************************/
bool	RPN::syntaxParser(const std::string& inputStr)
{
	size_t	i = 0;
	bool	hasContent = false;
	
	if (inputStr.empty())
		return (false);

	while (i < inputStr.length())
	{
		if (!isValidChar(inputStr[i]))
			return (false);

		if (!std::isspace(inputStr[i]))
			hasContent = true;

		if (i < inputStr.length() - 1)
		{
			if (std::isdigit(inputStr[i]) && std::isdigit(inputStr[i + 1]))
				return (false);
			
			if (isValidOperator(inputStr[i]) && isValidOperator(inputStr[i + 1]))
				return (false);
		}
		i++;
	}
	return (hasContent);
}

bool	RPN::isValidChar(char c)
{
	if (!std::isdigit(c) && c != '*'
			&& c != '-' && c != '+'
			&& c != '/' && !std::isspace(c))
	{
		return (false);
	}
	return (true);
}

bool	RPN::isValidOperator(char c)
{
	if (c == '+' || c == '-' || c == '*' || c == '/')
		return (true);
	return (false);
}
