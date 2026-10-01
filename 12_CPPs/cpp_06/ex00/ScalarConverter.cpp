/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 07:21:17 by mzolotar          #+#    #+#             */
/*   Updated: 2025/11/06 10:28:38 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"

/******************************************************************************/
/*						CONSTRUCTORS & DESTRUCTORS							  */
/******************************************************************************/
/*	Default Constructor		*/
ScalarConverter::ScalarConverter (void)	{}

/*	Copy Constructor		*/
ScalarConverter::ScalarConverter(const ScalarConverter &other)
{
	(void)other;
}

/*	Desctructor				*/
ScalarConverter::~ScalarConverter() {}

/******************************************************************************/
/*								OPERATORS								  	  */
/******************************************************************************/
/*	Copy Assignment Operator	*/
ScalarConverter& ScalarConverter::operator=(ScalarConverter const &other)
{
	(void)other;
	return (*this);
}


/******************************************************************************/
/*							PUBLIC METHODS									  */
/******************************************************************************/
void ScalarConverter::convert(const std::string& str)
{
	e_type type = checkType(str);

	switch (type)
	{
		case TYPE_ERROR:
			std::cout << "Invalid input" << std::endl;
			break;
		case TYPE_ERROR_E:
			std::cout << "This program does not parse numbers with exponents." << std::endl;
			break;
		case TYPE_SPECIAL:
			printSpecial(str);
			break;
		case TYPE_CHAR:
			convertChar(str);
			break;
		case TYPE_INT:
			convertInt(str);
			break;
		case TYPE_FLOAT:
			convertFloat(str);
			break;
		case TYPE_DOUBLE:
			convertDouble(str);
			break;
	}
}
