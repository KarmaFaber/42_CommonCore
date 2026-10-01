/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScavTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 10:08:35 by mzolotar          #+#    #+#             */
/*   Updated: 2025/09/25 08:44:25 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScavTrap.hpp"

/******************************************************************************/
/*						CONSTRUCTORS & DESTRUCTORS							  */
/******************************************************************************/

/*	Default Constructor	*/
ScavTrap::ScavTrap(void)
		  : ClapTrap("ScavTrap_default")
{
	std::cout << CCYAN << "ScavTrap Default Attribute constructor called" << CRESET << std::endl;
	setHitPoints (100);
	setEnergyPoints (50);
	setAttackDamage (20);
}

/*	Atribute Constructor	*/
ScavTrap::ScavTrap(std::string name)
	: ClapTrap(name) {
	std::cout << CCYAN << "ScavTrap Attribute constructor called"
			  << CRESET << std::endl;
	setHitPoints (100);
	setEnergyPoints (50);
	setAttackDamage (20);
}

/*	Copy Constructor		*/
ScavTrap::ScavTrap (const ScavTrap& other)
	: ClapTrap(other) {
	std::cout << CCYAN << "ScavTrap Copy constructor called"
			  << CRESET << std::endl;
}

/*	Desctructor				*/
ScavTrap::~ScavTrap() {
	std::cout << CCYAN << "ScavTrap Destructor called" << CRESET << std::endl;
}

/******************************************************************************/
/*								OPERATORS								  	  */
/******************************************************************************/
/*	Copy Assignment Operator	*/

ScavTrap& ScavTrap::operator=(const ScavTrap& other) {
    std::cout << CCYAN << "ScavTrap Copy assignment operator called"
			  << CRESET << std::endl;
    if (this != &other)
    {
        this->setName(other.getName());
        this->setHitPoints(other.getHitPoints());
        this->setEnergyPoints(other.getEnergyPoints());
        this->setAttackDamage(other.getAttackDamage());
    }
    return (*this);
}

/******************************************************************************/
/*							PUBLIC FUNCTIONS								  */
/******************************************************************************/

void	ScavTrap::attack(const std::string& target) {
	if ( getHitPoints() <= 0)
	{
		std::cout << CRED << "ScavTrap "
				  << getName() << " is already dead." << CRESET <<  std::endl;
		return ;
	}
	if ( getEnergyPoints() <= 0 )
	{
		std::cout << CRED << "ScavTrap "
				  << getName() << " has no energy." << CRESET << std::endl;
		return ;
	}
	std::cout << CCYAN << "ScavTrap "
			  << getName() << " attacks " << target
			  << ", causing " << getAttackDamage()
			  << " points of damage!" << CRESET << std::endl;
	setEnergyPoints( getEnergyPoints() - 1 );
}

void	ScavTrap::guardGate( void ) {
	if ( getHitPoints() <= 0)
	{
		std::cout << CRED << "ScavTrap "
				  << getName() << " is already dead." << CRESET <<  std::endl;
		return ;
	}
	std::cout << CCYAN << "ScavTrap "
			  << getName() << " is now in Gate keeper mode."
			<< CRESET << std::endl;
}
