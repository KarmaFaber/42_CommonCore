/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 11:52:18 by mzolotar          #+#    #+#             */
/*   Updated: 2026/02/17 19:25:04 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <exception>
#include <string>
#include <cstdlib>

#include "utils/ErrorException.hpp"
#include "utils/Utils.hpp"

class BitcoinExchange
{
	private:
		std::map<std::string, double>	_quotes;

		void			readDataBase(const std::string& dataFileName);
		bool			validateDate(std::string const &date);
		double			validatePrice(std::string const &price);
		void			multiplyWithQuote(std::string const &date, double price);
		std::string		trim(const std::string& str);
		void			processLine(std::string const &line);
	
	public:
		BitcoinExchange(void);
		BitcoinExchange(BitcoinExchange const &other);
		BitcoinExchange &operator=(BitcoinExchange const &other);
		~BitcoinExchange();

		std::map<std::string, double> const&	getQuotes(void) const;

		void			execute(char const *inputFileName);
};

#endif