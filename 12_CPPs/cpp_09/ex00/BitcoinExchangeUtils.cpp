/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchangeUtils.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 11:19:59 by mzolotar          #+#    #+#             */
/*   Updated: 2026/02/17 20:22:27 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

/******************************************************************************/
/*							PRIVATE METHODS									  */
/******************************************************************************/

void	BitcoinExchange::readDataBase(const std::string& dataFileName)
{
	std::ifstream file(dataFileName.c_str());
	if (!file.is_open())
		throw (ErrorException("could not open Data File."));

	std::string line;
	std::getline(file, line);
	if (line != "date,exchange_rate")
		throw (ErrorException("invalid column format. Expected 'date,exchange_rate'"));

	while (std::getline(file, line))
	{
		size_t commaPos = line.find(',');
		if (commaPos == std::string::npos)
			throw (ErrorException("invalid column format. Expected ',' between date and exchange_rate"));
		else if (commaPos != std::string::npos)
		{
			std::string date = line.substr(0, commaPos);
			if (!validateDate(date))
				throw (ErrorException("wrong date in Data File."));
			double rate = atof(line.substr(commaPos + 1).c_str());
			_quotes[date] = rate;
		}
	}
	if (_quotes.empty())
		throw (ErrorException("database is empty."));
	file.close();
}

bool	BitcoinExchange::validateDate(std::string const &date)
{
	if (date.size() != 10 || date[4] != '-' || date[7] != '-')
		return (false);
	for (int i = 0; i < 10; i++)
	{
		if (i == 4 || i == 7)
			continue;
		if (!isdigit(date[i]))
			return (false);
	}
	int year = atoi(date.substr(0, 4).c_str());
	int month = atoi(date.substr(5, 2).c_str());
	int day = atoi(date.substr(8, 2).c_str());
	if (month < 1 || month > 12)
		return (false);
	if (day < 1 || day > 31)
		return (false);
	if (month == 4 || month == 6 || month == 9 || month == 11)
	{
		if (day > 30)
			return (false);
	}
	if (month == 2)
	{
		bool isLeap = (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
		if (isLeap && day > 29)
			return (false);
		if (!isLeap && day > 28)
			return (false);
	}
	return (true);
}

double	BitcoinExchange::validatePrice(std::string const &price)
{
	double priceValue;
	std::istringstream priceStream(price);

	if (!(priceStream >> priceValue))
	{
		std::cerr << CMAGENTA << "Error: bad value input => " << priceValue << CRESET << std::endl;
		return (-1);
	}

	if (priceValue < 0)
	{
		showErrorMsg(CMAGENTA, "Error: not a positive number.", CRESET);
		return (-1);
	}
	else if (priceValue > 1000)
	{
		showErrorMsg(CMAGENTA, "Error: too large number.", CRESET);
		return (-1);
	}
	return (priceValue);
}

void	BitcoinExchange::multiplyWithQuote(std::string const &date, double price)
{
	std::map<std::string, double>::const_iterator it = _quotes.lower_bound(date);

	if (it != _quotes.end() && it->first == date)
	{
		std::cout << date << " => " << price << " = " << price * it->second << std::endl;
	}
	else
	{
		if (it == _quotes.begin())
		{
			std::cerr << "Error: date too early => " << date << std::endl;
		}
		else
		{
			--it;
			std::cout << date << " => " << price << " = " << price * it->second << std::endl;
		}
	}
}

std::string	BitcoinExchange::trim(const std::string& str)
{
	size_t first = str.find_first_not_of(" \t\r\n");
	if (first == std::string::npos)
		return "";
	size_t last = str.find_last_not_of(" \t\r\n");
	return str.substr(first, (last - first + 1));
}

void	BitcoinExchange::processLine(std::string const &line)
{
	size_t pipePos = line.find('|');
	if (pipePos == std::string::npos)
	{
		std::cerr << CMAGENTA << "Error: bad input => " << line << CRESET << std::endl;
		return;
	}

	std::string date = trim(line.substr(0, pipePos));
	std::string valStr = trim(line.substr(pipePos + 1));

	if (!validateDate(date))
	{
		std::cerr << CMAGENTA << "Error: bad input => " << date << CRESET << std::endl;
		return;
	}

	double val = validatePrice(valStr);
	if (val >= 0)
		multiplyWithQuote(date, val);
}
