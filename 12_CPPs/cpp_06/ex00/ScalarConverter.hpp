/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 07:21:17 by mzolotar          #+#    #+#             */
/*   Updated: 2025/11/06 10:14:59 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCALARCONVERTE_HPP
#define SCALARCONVERTE_HPP

#define NOT_DISPLAYABLE		"Non displayable"
#define IMPOSIBLE			"impossible"

#include <iostream>
#include <string>
#include <limits>		// para límites numéricos
#include <cstdlib>		// para strtod, strtof, atoi
#include <cmath>		// para isnan, isinf
#include <cctype>		// para isdigit

enum e_type
{
	TYPE_ERROR,
	TYPE_ERROR_E,
	TYPE_SPECIAL,
	TYPE_CHAR,
	TYPE_INT,
	TYPE_FLOAT,
	TYPE_DOUBLE
};

class ScalarConverter 
{
	private:
		ScalarConverter (void);
		ScalarConverter(const ScalarConverter &other);
		~ScalarConverter();
		ScalarConverter& operator=(ScalarConverter const &other);

	public:
		static void	convert(const std::string& str);
};

// ---------- PRINTERS ----------
void		printChar(double value);
void		printInt(double value);
void		printFloat(double value, bool tolerance);
void		printDouble(double value, bool tolerance);

// ---------- CONVERTERS ----------
e_type		checkType(const std::string& str);
void		printSpecial(const std::string& str);
void		convertChar(const std::string& str);
void		convertInt(const std::string& str);
void		convertFloat(const std::string& str);
void		convertDouble(const std::string& str);

#endif
