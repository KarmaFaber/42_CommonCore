/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 08:04:01 by mzolotar          #+#    #+#             */
/*   Updated: 2025/09/25 08:31:18 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"

/******************************************************************************/
/*						CONSTRUCTORS & DESTRUCTORS							  */
/******************************************************************************/

/*	Default Constructor	*/
ClapTrap::ClapTrap(void)
		  : _name("name_default"),
		  _hit_points(0),
		  _energy_points(0),
		  _attack_damage(0)
{
	std::cout << CGREEN << "ClapTrap Default Attribute constructor called"
			  << CRESET << std::endl;
}

/*	Attribute Constructor	*/
ClapTrap::ClapTrap(std::string name)
		  :_name(name),
		  _hit_points(10),
		  _energy_points(10),_attack_damage(0)
{
	std::cout << CGREEN << "ClapTrap Attribute constructor called" << CRESET << std::endl;
}

/*	Copy Constructor	*/
ClapTrap::ClapTrap(const ClapTrap& other)
		: _name(other._name),
		  _hit_points(other._hit_points),
		  _energy_points(other._energy_points),
		  _attack_damage(other._attack_damage)
{
	std::cout << CGREEN << "ClapTrap Copy constructor called" << CRESET << std::endl;
}

/*	Desctructor	*/
ClapTrap::~ClapTrap()
{
	std::cout << CGREEN << "ClapTrap Destructor called" << CRESET << std::endl;
}

/******************************************************************************/
/*								OPERATORS								  	  */
/******************************************************************************/

/*	Copy Assignment Operator	*/
ClapTrap& ClapTrap::operator=(const ClapTrap& other)
{
	std::cout << CGREEN << "ClapTrap Copy assignment operator called"
			  << CRESET << std::endl;
	if (this != &other)
	{
		this->_name = other.getName();
		this->_hit_points = other.getHitPoints();
		this->_energy_points = other.getEnergyPoints();
		this->_attack_damage = other.getAttackDamage();
	}
	return (*this);
}

/******************************************************************************/
/*								GETTERS										  */
/******************************************************************************/

std::string		ClapTrap::getName( void ) const
{
	return (_name);
}

unsigned int	ClapTrap::getHitPoints( void ) const
{
	return (_hit_points);
}

unsigned int	ClapTrap::getEnergyPoints( void ) const
{
	return (_energy_points);
}

unsigned int	ClapTrap::getAttackDamage( void ) const
{
	return (_attack_damage);
}

/******************************************************************************/
/*								SETTERS										  */
/******************************************************************************/
void	ClapTrap::setName(std::string name)
{
	_name = name;
}

void	ClapTrap::setHitPoints(int hp)
{
	if (hp < 0)
		_hit_points = 0;
	else
		_hit_points = hp;
}

void	ClapTrap::setEnergyPoints(int ep)
{
	if (ep < 0)
		_energy_points = 0;
	else
		_energy_points = ep;
}

void	ClapTrap::setAttackDamage(int ad)
{
	if (ad < 0)
		_attack_damage = 0;
	else
		_attack_damage = ad;
}

/******************************************************************************/
/*							PUBLIC FUNCTIONS								  */
/******************************************************************************/

void	ClapTrap::attack(const std::string& target)
{
	if ( getHitPoints() <= 0)
	{
		std::cout << CRED << "ClapTrap "
				  << getName() << " is already dead." << CRESET <<  std::endl;
		return ;
	}
	if ( getEnergyPoints() <= 0 )
	{
		std::cout << CRED << "ClapTrap "
				  << getName() << " has no energy." << CRESET << std::endl;
		return ;
	}
	setEnergyPoints(getEnergyPoints() - 1);
	std::cout << CGREEN << "ClapTrap " << getName()
			  << " attacks " << target << ", causing "
			  << getAttackDamage() << " points of damage!"
			  << CRESET << std::endl;
}

void	ClapTrap::takeDamage(unsigned int amount)
{
	if ( getHitPoints() <= 0)
	{
		std::cout << CRED << "ClapTrap " << getName()
				  << " is already dead." << CRESET << std::endl;
		return ;
	}
	setHitPoints(getHitPoints() - amount);
	std::cout << CGREEN << "ClapTrap " << getName()
			  << " takes " << amount 
			  << " points of damage! Remaining HP: " 
			  << getHitPoints() << CRESET << std::endl;
	if (getHitPoints() == 0)
	{
		std::cout << CRED << "ClapTrap "
				  << getName() << " has died!" << CRESET << std::endl;
	}
}

void	ClapTrap::beRepaired(unsigned int amount)
{
	if ( getHitPoints() <= 0)
	{
		std::cout << CRED << "ClapTrap " << getName()
				  << " is already dead and cannot be repaired."
				  << CRESET << std::endl;
		return ;
	}
	if (getEnergyPoints() <= 0)
	{
		std::cout << CRED << "ClapTrap " << getName()
				  << " has no energy to repair."
				  << CRESET << std::endl;
		return;
	}
	setEnergyPoints(getEnergyPoints() - 1);
	setHitPoints(getHitPoints() + amount);
	std::cout << CGREEN << "ClapTrap " << getName()
			  << " repairs itself for "
			  << amount << " hit points! Current HP: "
			  << getHitPoints() << CRESET << std::endl;
}
