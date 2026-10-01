/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FragTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 22:44:02 by mzolotar          #+#    #+#             */
/*   Updated: 2025/09/25 08:47:44 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FragTrap.hpp"

/******************************************************************************/
/*						CONSTRUCTORS & DESTRUCTORS							  */
/******************************************************************************/

/*	Default Constructor	*/
FragTrap::FragTrap(void)
		  : ClapTrap("FragTrap_default")
{
	std::cout << CYELLOW << "FragTrap Default Attribute constructor called"
			  << CRESET << std::endl;
	setHitPoints (100);
	setEnergyPoints (100);
	setAttackDamage (30);
}

/*	Atribute Constructor	*/
FragTrap::FragTrap(std::string name)
		  : ClapTrap(name)
{
	std::cout << CYELLOW << "FragTrap Attribute constructor called"
			  << CRESET << std::endl;
	setName(name);
	setHitPoints(100);
	setEnergyPoints(100);
	setAttackDamage(30);
}

/*	Copy Constructor		*/
FragTrap::FragTrap (const FragTrap& other)
		  : ClapTrap(other)
{
	std::cout << CYELLOW << "FragTrap Copy constructor called"
			  << CRESET << std::endl;
}

/*	Desctructor				*/
FragTrap::~FragTrap()
{
	std::cout << CYELLOW << "FragTrap Destructor called" << CRESET << std::endl;
}

/******************************************************************************/
/*								OPERATORS								  	  */
/******************************************************************************/

/*	Copy Assignment Operator	*/
FragTrap& FragTrap::operator=(const FragTrap& other)
{
	std::cout << CYELLOW << "FragTrap Copy assignment operator called"
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
/*								GETTERS										  */
/******************************************************************************/

unsigned int	FragTrap::getAttackDamageDefault( void ) const
{
	return ( 30 );
}

unsigned int	FragTrap::getHitPointsDefault( void ) const
{
	return ( 100 );
}

/******************************************************************************/
/*							PUBLIC FUNCTIONS								  */
/******************************************************************************/

void	FragTrap::highFivesGuys(void)
{
	if ( getHitPoints() <= 0)
	{
		std::cout << CRED << "FragTrap "
				  << getName() << " is already dead." << CRESET <<  std::endl;
		return ;
	}
	std::cout << CYELLOW << "FragTrap " << getName()
			  << " is requesting a high five! ✋" << CRESET << std::endl;
}
