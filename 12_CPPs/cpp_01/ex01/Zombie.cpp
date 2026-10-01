/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 10:17:28 by mzolotar          #+#    #+#             */
/*   Updated: 2025/09/24 08:25:18 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

/******************************************************************************/
/*						CONSTRUCTORS & DESTRUCTORS							  */
/******************************************************************************/

Zombie::Zombie(void) 
{
	std::cout << CBLUE << "zombie created (default constructor)" << CRESET << std::endl;
}

Zombie::Zombie(const std::string& input_name)
{
	_name = input_name;
	std::cout << CBLUE << _name << " created" << CRESET << std::endl;
}

Zombie::~Zombie()
{
	std::cout << CBLUE << _name << " died." << CRESET << std::endl;
}

/******************************************************************************/
/*								GETTERS										  */
/******************************************************************************/

const std::string& Zombie::getName(void) const
{
	return (_name);
}

/******************************************************************************/
/*								SETTERS										  */
/******************************************************************************/

void Zombie::setName(const std::string& str_name)
{
	_name = str_name;
}

/******************************************************************************/
/*							PUBLIC FUNCTIONS								  */
/******************************************************************************/

void Zombie::announce(void)
{
	std::cout << CGREEN << _name << ":  BraiiiiiiinnnzzzZ..." << CRESET << std::endl;
}
