/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 11:52:24 by mzolotar          #+#    #+#             */
/*   Updated: 2026/02/17 20:21:24 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

/******************************************************************************/
/*						CONSTRUCTORS & DESTRUCTORS							  */
/******************************************************************************/

/*	Default Constructor		*/
BitcoinExchange::BitcoinExchange(void)
{
	readDataBase("data.csv");
}

/*	Copy Constructor		*/
BitcoinExchange::BitcoinExchange(BitcoinExchange const &other) 
{
	if (this != &other)
		*this = other;
}

/*	Desctructor				*/
BitcoinExchange::~BitcoinExchange() {}

/******************************************************************************/
/*								OPERATORS								  	  */
/******************************************************************************/

/*	Copy Assignment Operator	*/
BitcoinExchange& BitcoinExchange::operator=(BitcoinExchange const &other)
{
	if (this != &other)
		_quotes = other._quotes;
	return (*this);
}

/******************************************************************************/
/*								GETTERS										  */
/******************************************************************************/

std::map<std::string, double> const&	BitcoinExchange::getQuotes(void) const
{
	return (_quotes);
}

/******************************************************************************/
/*							PUBLIC METHODS									  */
/******************************************************************************/

void	BitcoinExchange::execute(char const *inputFileName)
{
	std::ifstream file(inputFileName);
	if (!file.is_open())
		throw (ErrorException("could not open Input file."));

	std::string line;
	if (!std::getline(file, line))
		throw (ErrorException("Empty Input file."));

	if (trim(line) != "date | value")
		throw (ErrorException("invalid column format in Input File."));

	bool hasData = false;
	while (std::getline(file, line))
	{
		if (line.empty() || line.find_first_not_of(" \t\r\n") == std::string::npos)
			continue;
		hasData = true;
		processLine(line);
	}
	if (!hasData)
		std::cerr << CMAGENTA << "Warning: no data entries found." << CRESET << std::endl;
	file.close();
}
