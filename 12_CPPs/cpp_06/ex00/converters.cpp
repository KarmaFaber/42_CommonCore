/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   converters.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 08:38:07 by mzolotar          #+#    #+#             */
/*   Updated: 2025/11/06 10:09:37 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"
#include "checkers.hpp"

// ---------- PRINTERS ----------
void printChar(double value)
{
	std::cout << "char: ";
	if (value < 0 || value > 127 || std::isnan(value) || std::isinf(value))
		std::cout << IMPOSIBLE << std::endl;
	else
	{
		if (isprint(static_cast<int>(value)))
			std::cout << "'" << static_cast<char>(value) << "'" << std::endl;
		else
			std::cout << NOT_DISPLAYABLE << std::endl;
	}
}

void printInt(double value)
{
	std::cout << "int: ";
	if (std::isnan(value) || std::isinf(value)
		|| value < static_cast<double>(std::numeric_limits<int>::min())
		|| value > static_cast<double>(std::numeric_limits<int>::max()))
		std::cout << IMPOSIBLE << std::endl;
	else
		std::cout << static_cast<int>(value) << std::endl;
}

void printFloat(double value, bool tolerance)
{
	std::cout << "float: ";
	if (std::isnan(value))
		std::cout << "nanf" << std::endl;
	else if (std::isinf(value))
	{
		if (value > 0)
			std::cout << "+inff" << std::endl;
		else
			std::cout << "-inff" << std::endl;
	}
	else if (value < -std::numeric_limits<float>::max()
			|| value > std::numeric_limits<float>::max())
		std::cout << IMPOSIBLE << std::endl;
	else
	{
		std::cout << static_cast<float>(value);
		if (tolerance)
			std::cout << ".0f";
		else
			std::cout << "f";
		std::cout << std::endl;
	}
}

void printDouble(double value, bool tolerance)
{
	std::cout << "double: ";
	if (std::isnan(value))
		std::cout << "nan" << std::endl;
	else if (std::isinf(value))
	{
		if (value > 0)
			std::cout << "+inf" << std::endl;
		else
			std::cout << "-inf" << std::endl;
	}
	else if (value < -std::numeric_limits<double>::max()
			|| value > std::numeric_limits<double>::max())
		std::cout << IMPOSIBLE << std::endl;
	else
	{
		std::cout << value;
		if (tolerance)
			std::cout << ".0";
		std::cout << std::endl;
	}
}

// ---------- CONVERTERS ----------
e_type	checkType(const std::string& str)
{
	size_t	dot = str.find('.');
	size_t	f = str.find('f');
	size_t	e = str.find('e');
	
	if (dot == std::string::npos)
	{
		if (checkSpecial(str))
			return (TYPE_SPECIAL);
		else if (checkChar(str))
			return (TYPE_CHAR);
		else if (checkInt(str))
			return (TYPE_INT);
	}
	else if (e != std::string::npos)
	{
		return (TYPE_ERROR_E);
	}
	else if (f != std::string::npos && dot != std::string::npos)
	{
		if (checkFloat(str, dot))
			return (TYPE_FLOAT);
	}
	else if (f == std::string::npos && dot != std::string::npos)
		return (TYPE_DOUBLE);
	return (TYPE_ERROR);
}

void	printSpecial(const std::string& str)
{
	if (str == "nan" || str == "nanf")
	{
		std::cout << "char: impossible" << std::endl; 
		std::cout << "int: impossible" << std::endl;
		std::cout << "float: nanf" << std::endl;
		std::cout << "double: nan" << std::endl;
	}
	else if (str == "+inf" || str == "+inff")
	{
		std::cout << "char: impossible" << std::endl;
		std::cout << "int: impossible" << std::endl;
		std::cout << "float: +inff" << std::endl;
		std::cout << "double: +inf" << std::endl;
	}
	else if (str == "-inf" || str == "-inff")
	{
		std::cout << "char: impossible" << std::endl;
		std::cout << "int: impossible" << std::endl;
		std::cout << "float: -inff" << std::endl;
		std::cout << "double: -inf" << std::endl;
	}
}

void	convertChar(const std::string& str)
{
	char	c = 0;

	if (str.length() == 1)
		c = str[0];
	else
		c = str[1];
	std::cout << "char: ";
	if (isprint(c))
	{
		std::cout << "'" << c << "'" << std::endl;
		std::cout << "int: " << static_cast<int>(c) << std::endl;
		std::cout << "float: " << static_cast<float>(c) << ".0f" << std::endl;
		std::cout << "double: " << static_cast<double>(c) << ".0" << std::endl;
	}
	else
		std::cout << NOT_DISPLAYABLE << std::endl;
}

void	convertInt(const std::string& str)
{
	long l = std::atol(str.c_str());
	double value = static_cast<double>(l);

	printChar(value);
	printInt(value);
	printFloat(value, true);
	printDouble(value, true);
}

void convertFloat(const std::string& str)
{
	float f = std::atof(str.c_str());
	bool tolerance = (std::fabs(f - static_cast<int>(f)) < 0.0000000000001);

	printChar(f);
	printInt(f);
	printFloat(f, tolerance);
	printDouble(f, tolerance);
}

void	convertDouble(const std::string& str)
{
	double d = std::atof(str.c_str());
	bool tolerance = (std::fabs(d - static_cast<int>(d)) < 0.0000000000001);

	printChar(d);
	printInt(d);
	printFloat(d, tolerance);
	printDouble(d, tolerance);
}
