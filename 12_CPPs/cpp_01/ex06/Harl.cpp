/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Harl.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 13:39:36 by mzolotar          #+#    #+#             */
/*   Updated: 2025/09/04 09:26:00 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Harl.hpp"

/******************************************************************************/
/*						CONSTRUCTORS & DESTRUCTORS							  */
/******************************************************************************/

Harl::Harl(void) {}

Harl::~Harl () {}

/******************************************************************************/
/*							PRIVATE FUNCTIONS								  */
/******************************************************************************/

void	Harl::debug( void )
{
	std::cout << DEBUG << std::endl;
}

void	Harl::info( void )
{
	std::cout << INFO << std::endl;
}

void	Harl::warning( void )
{
	std::cout << WARNING << std::endl;
}

void	Harl::error( void )
{
	std::cout << ERROR << std::endl;
}

/******************************************************************************/
/*							PUBLIC FUNCTIONS								  */
/******************************************************************************/

void	Harl::complain( std::string level)
{
	void (Harl::*functionPtrs[])(void) =
			  { &Harl::debug, &Harl::info, &Harl::warning, &Harl::error };
	std::string levels[] =
			  { "DEBUG", "INFO", "WARNING", "ERROR" };
	int i;
	for (i = 0; i < 4; i++)
	{
		if (levels[i] == level)
			break;
	}
	switch(i)
	{
		case(0):
			(this->*functionPtrs[0])();
			/* fall through */
		case(1):
			(this->*functionPtrs[1])();
			/* fall through */
		case(2):
			(this->*functionPtrs[2])();
			/* fall through */
		case(3):
			(this->*functionPtrs[3])();
			break;
		
		default:
			std::cout << DEFAULT << std::endl;
	}
}
