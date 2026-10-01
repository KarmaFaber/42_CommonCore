/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Harl.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 13:39:36 by mzolotar          #+#    #+#             */
/*   Updated: 2025/09/04 09:24:15 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Harl.hpp"

/******************************************************************************/
/*						CONSTRUCTORS & DESTRUCTORS							  */
/******************************************************************************/

Harl::Harl(void) {}

Harl::~Harl() {}

/******************************************************************************/
/*							PRIVATE FUNCTIONS								  */
/******************************************************************************/

void	Harl::debug( void )
{
	std::cout << DEBUG << std::endl;
}

void	Harl::info( void )
{
	std::cout << 	INFO << std::endl;
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
	for (int i = 0; i < 4; i++)
	{
		if (levels[i] == level)
		{
			(this->*functionPtrs[i])();
			return;
		}
	}
	std::cout << CRED << "Invalid level: " << level << CRESET << std::endl;
}
