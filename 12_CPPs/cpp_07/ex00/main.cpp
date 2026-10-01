/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 12:44:15 by mzolotar          #+#    #+#             */
/*   Updated: 2025/11/07 08:18:23 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "whatever.hpp"

#define CRED				"\033[0;31m"
#define CGREEN				"\033[0;32m"
#define CMAGENTA			"\033[0;35m"
#define CCYAN				"\e[36m"
#define CRESET				"\033[0m"


int main( void )
{
	int a = 2;
	int b = 3;
	::swap( a, b );
	std::cout << "a = " << a << ", b = " << b << std::endl;
	std::cout << "min( a, b ) = " << ::min( a, b ) << std::endl;
	std::cout << "max( a, b ) = " << ::max( a, b ) << std::endl;
	std::string c = "chaine1";
	std::string d = "chaine2";
	::swap(c, d);
	std::cout << "c = " << c << ", d = " << d << std::endl;
	std::cout << "min( c, d ) = " << ::min( c, d ) << std::endl;
	std::cout << "max( c, d ) = " << ::max( c, d ) << std::endl;
	return 0;
}


/*
int main( void )
{
	//INT
	std::cout << "-------INT-------" << std::endl;
	int a = 2;
	int b = 3;
	std::cout << CMAGENTA <<  "original ->  " << CRESET
			  << "a = " << a << ", b = " << b << std::endl;
	::swap( a, b );
	std::cout << CCYAN << "swaped   ->  " << CRESET << "a = "
			  << a << ", b = " << b << std::endl;
	std::cout << "min( a, b ) = " << ::min( a, b ) << std::endl;
	std::cout << "max( a, b ) = " << ::max( a, b ) << std::endl;
	std::cout << "-------\n" << std::endl;

	//STR
	std::cout << "-------STR-------" << std::endl;
	std::string c = "unicorn";
	std::string d = "another random animal";
	std::cout << CMAGENTA <<  "original ->  "
			  << CRESET << "c = " << c << ", d = " << d << std::endl;
	::swap(c, d);
	std::cout << CCYAN << "swaped   ->  "
			  << CRESET << "c = " << c << ", d = " << d << std::endl;
	std::cout << "min( c, d ) = " << ::min( c, d ) << std::endl;
	std::cout << "max( c, d ) = " << ::max( c, d ) << std::endl;
	std::cout << "-------\n" << std::endl;

	//FLOAT
	std::cout << "-------FLOAT-------" << std::endl;
	float f = 1.2, e = 3.4;
	std::cout << CMAGENTA <<  "original ->  "
			  << CRESET << "f = " << f << ", e = " << e << std::endl;
	::swap(f, e);
	std::cout << CCYAN << "swaped   ->  "
			  << CRESET << "f = " << f << ", e = " << e << std::endl;
	std::cout << "min( f, e ) = " << ::min( f, e ) << std::endl;
	std::cout << "max( f, e ) = " << ::max( f, e ) << std::endl;

	return (0);
}
*/
