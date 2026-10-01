/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parserInput.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 09:19:17 by mzolotar          #+#    #+#             */
/*   Updated: 2026/02/17 18:52:12 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../PmergeMe.hpp"

/******************************************************************************/
/*							PRIVATE METHODS									  */
/******************************************************************************/

bool	PmergeMe::parseInput(int argc, char **argv)
{
	std::stringstream	ss;
	std::string			str_token;

	for (int i = 1; i < argc; ++i)
	{
		ss << argv[i] << " ";
	}

	while (ss >> str_token)
	{
		if(hasSyntaxError(str_token))
			return (false);

		long long_token = convertLong(str_token);
		
		if (hasLogicError(long_token))
			return (false);

		_before_data.push_back(static_cast<int>(long_token));
	}

	if (_before_data.empty())
		return (false);
	if (isRepetedValue(_before_data))
		return (false);
	return (true);
}

bool	PmergeMe::hasSyntaxError(std::string str_token)
{
	if (str_token.empty())
		return (true);

	for (size_t i = 0; i < str_token.length(); ++i)
	{
		if (str_token[i] == '+')
		{
			if (i != 0 || str_token.length() == 1)
				return (true);
		}
		else if (!std::isdigit(str_token[i]))
			return (true);
	}
	return (false);
}

bool	PmergeMe::hasLogicError(long long_token)
{
	if (long_token < 0)
		return (true);
	if (long_token > INT_MAX)
		return (true);
	return (false);
}

bool	PmergeMe::isRepetedValue(std::vector<int> &before_data)
{
	std::set<int> seen;

	for (size_t i = 0; i < before_data.size(); ++i)
	{
		if (!seen.insert(before_data[i]).second)
			return (true);
	}
	return (false);
}


long	PmergeMe::convertLong(std::string str_token)
{
	long value = std::atol(str_token.c_str());
	return (value);
}
