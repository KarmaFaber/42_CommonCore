/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanB.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 11:46:10 by mzolotar          #+#    #+#             */
/*   Updated: 2025/08/29 08:49:33 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HumanB.hpp"
#include "Weapon.hpp"

/******************************************************************************/
/*						CONSTRUCTORS & DESTRUCTORS							  */
/******************************************************************************/

HumanB::HumanB(const std::string& str_name_b)
			: _name_b(str_name_b), _weapon_b(NULL) {}

HumanB::~HumanB() {}

/******************************************************************************/
/*								SETTERS										  */
/******************************************************************************/

void HumanB::setWeapon(Weapon& weapon_b)
{
	_weapon_b = &weapon_b;
}

/******************************************************************************/
/*							PUBLIC FUNCTIONS								  */
/******************************************************************************/

void HumanB::attack(void) const
{
	if (_weapon_b)
	{
		std::cout << CGREEN << _name_b << " attacks with their "
				  << _weapon_b->getType() << "." << CRESET << std::endl;
	}
	else
	{
		std::cout << CGREEN << this->_name_b
				  << " attacks with his fists." << CRESET << std::endl;
	}
}
