/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanA.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 11:46:01 by mzolotar          #+#    #+#             */
/*   Updated: 2025/08/29 08:48:38 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HumanA.hpp"
#include "Weapon.hpp"

/******************************************************************************/
/*						CONSTRUCTORS & DESTRUCTORS							  */
/******************************************************************************/

HumanA::HumanA(const std::string& _str_name_a, Weapon& _str_weapon_a)
			  : _name_a(_str_name_a), _weapon_a(_str_weapon_a) {}

HumanA::~HumanA() {}

/******************************************************************************/
/*							PUBLIC FUNCTIONS								  */
/******************************************************************************/

void HumanA::attack(void) const
{
	std::cout << CGREEN << _name_a << " attacks with their " 
			  << _weapon_a.getType() << "." << CRESET << std::endl;
}
