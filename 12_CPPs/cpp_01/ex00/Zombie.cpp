/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 09:34:20 by mzolotar          #+#    #+#             */
/*   Updated: 2025/09/04 09:17:25 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

/******************************************************************************/
/*						CONSTRUCTORS & DESTRUCTORS							  */
/******************************************************************************/

Zombie::Zombie(void) {}

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
/*							PUBLIC FUNCTIONS								  */
/******************************************************************************/

void Zombie::announce(void)
{
	std::cout << CGREEN << _name << ":  BraiiiiiiinnnzzzZ..." << CRESET << std::endl;
}
