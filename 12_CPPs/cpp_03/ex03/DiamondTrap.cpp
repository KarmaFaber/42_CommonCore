/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DiamondTrap.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 22:58:39 by mzolotar          #+#    #+#             */
/*   Updated: 2025/09/25 08:58:52 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "DiamondTrap.hpp"

/******************************************************************************/
/*						CONSTRUCTORS & DESTRUCTORS							  */
/******************************************************************************/

/* Default Constructor */
DiamondTrap::DiamondTrap()
	: ClapTrap("DiamondTrap_clap_name"),
	  FragTrap(),
	  ScavTrap(),
	  _name("DiamondTrap_default")
{
	std::cout << CBLUE
			  << "DiamondTrap Default Constructor called"
			  << CRESET << std::endl;
	this->setHitPoints(FragTrap::getHitPointsDefault());
	this->setEnergyPoints(ScavTrap::getEnergyPointsDefault());
	this->setAttackDamage(FragTrap::getAttackDamageDefault());
}

/*	Atribute Constructor	*/
DiamondTrap::DiamondTrap(std::string name)
		  : ClapTrap(name),
			FragTrap(name),
			ScavTrap(name),
			_name(name)
{
	std::cout << CBLUE << "DiamondTrap Attribute constructor called"
			  << CRESET << std::endl;
	ClapTrap::setName(name + "_clap_name");
	this->setHitPoints(FragTrap::getHitPointsDefault());
	this->setEnergyPoints(ScavTrap::getEnergyPointsDefault());
	this->setAttackDamage(FragTrap::getAttackDamageDefault());
}

/*	Copy Constructor		*/
DiamondTrap::DiamondTrap(const DiamondTrap& other)
		  : ClapTrap(other.ClapTrap::getName()),
			FragTrap(other),
			ScavTrap(other),
			_name(other._name)
{
	std::cout << CBLUE << "DiamondTrap Copy constructor called"
			  << CRESET << std::endl;
	this->setHitPoints(other.getHitPoints());
	this->setEnergyPoints(other.getEnergyPoints());
	this->setAttackDamage(other.getAttackDamage());
}

/*	Desctructor				*/
DiamondTrap::~DiamondTrap()
{
	std::cout << CBLUE << "DiamondTrap Destructor called" << CRESET << std::endl;
}

/******************************************************************************/
/*								OPERATORS								  	  */
/******************************************************************************/
/*	Copy Assignment Operator	*/
DiamondTrap&	DiamondTrap::operator=(const DiamondTrap& other)
{
	std::cout << CBLUE << "DiamondTrap Copy assignment operator called"
			  << CRESET << std::endl;
	if (this != &other)
	{
		ClapTrap::operator=(other);
		FragTrap::operator=(other);
        ScavTrap::operator=(other);
		this->_name = other._name;
	}
	return (*this);
}

/******************************************************************************/
/*								GETTERS										  */
/******************************************************************************/

std::string	DiamondTrap::getDiamondName() const
{
	return this->_name;
}

/******************************************************************************/
/*							PUBLIC FUNCTIONS								  */
/******************************************************************************/

void	DiamondTrap::whoAmI()
{
		  std::cout << CBLUE 
		  << "DiamondTrap name: " << this->_name  
		  << " | ClapTrap name: " << ClapTrap::getName()
		  << CRESET << std::endl;
}
