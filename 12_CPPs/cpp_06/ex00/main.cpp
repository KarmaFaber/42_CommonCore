/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 07:21:21 by mzolotar          #+#    #+#             */
/*   Updated: 2025/11/05 08:28:34 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"
#include <iostream>

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cerr << "Usage: ./convert <literal>" << std::endl;
		std::cerr << "\nExamples of valid literals:" << std::endl;
		std::cerr << "  ./convert 'a'" << std::endl;
		std::cerr << "  ./convert 42" << std::endl;
		std::cerr << "  ./convert -4.2" << std::endl;
		std::cerr << "  ./convert 42.0f" << std::endl;
		std::cerr << "  ./convert nan" << std::endl;
		std::cerr << "  ./convert +inff" << std::endl;
		std::cerr << "  ./convert -inf" << std::endl;
		return 1;
	}

	ScalarConverter::convert(argv[1]);
	return 0;
}


// ─── CHAR ───
//"'a'", "'Z'", "'0'",

// ─── INT ───
//"0", "-42", "42", "2147483647", "-2147483648",  // límites de int

// ─── FLOAT ───
//"0.0f", "-4.2f", "4.2f", "42.0f", "123456789.0f", 
//"-inff", "+inff", "nanf",

// ─── DOUBLE ───
//"0.0", "-4.2", "4.2", "42.0", "123456789.0",
//"-inf", "+inf", "nan",

// ─── ERRORES ───
//"abc", "4.2ff", "4..2", "nanff", "", "42f0", "++42", "--3.14"








