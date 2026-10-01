/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Character.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 13:43:14 by mzolotar          #+#    #+#             */
/*   Updated: 2025/10/28 10:06:58 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Character.hpp"

/******************************************************************************/
/*						CONSTRUCTORS & DESTRUCTORS							  */
/******************************************************************************/
/*	Default Constructor		*/
Character::Character(void)
		  : _name("default_name"), _floorIndex(0)
{
	std::cout << PURPLE << CHAR_DEF_CTOR << RESET << std::endl;
	for(int i =0; i < I_SIZE; i++)
	{
		this->_inventory[i] = NULL;
		this->_floor[i] = NULL;
	}
}

/*	Atribute Constructor	*/
Character::Character(std::string const& name)
		  : _name(name), _floorIndex(0)
{
	std::cout << PURPLE << CHAR_ARG_CTOR << RESET << std::endl;
	for(int i =0; i< I_SIZE; i++)
	{
		this->_inventory[i] = NULL;
		this->_floor[i] = NULL;
	}
}

/*	Copy Constructor		*/
Character::Character(const Character& other)
{
	std::cout << PURPLE << CHAR_COPY_CTOR << RESET << std::endl;
	this->_name = other._name;
	for(int i=0; i < I_SIZE; i++)
	{
		if(other._inventory[i])
			this->_inventory[i] = other._inventory[i]->clone();
		else
			this->_inventory[i] = NULL;
	}
	for (int i = 0; i < I_SIZE; i++)
		this->_floor[i] = NULL;
}

/*	Desctructor				*/
Character::~Character()
{
	std::cout << PURPLE << CHAR_DTOR << RESET << std::endl;
	for (int i = 0; i < I_SIZE; i++)
	{
		if (this->_inventory[i])
		{
			delete this->_inventory[i];
			this->_inventory[i] = NULL;
		}
	}
	for (int i = 0; i < I_SIZE; i++)
	{
		if (_floor[i])
		{
			delete _floor[i];
			_floor[i] = NULL;
		}
	}
}

/******************************************************************************/
/*								OPERATORS								  	  */
/******************************************************************************/
/*	Copy Assignment Operator	*/
Character& Character::operator=(const Character& other)
{
	std::cout << PURPLE << CHAR_ASS_OP << RESET << std::endl;
	if (this == &other)
		return (*this);
	this->_name = other._name;
	for (int i = 0; i < I_SIZE; i++)
	{
		if (this->_inventory[i])
		{
			delete this->_inventory[i];
			this->_inventory[i] = NULL;
		}
	}
	for (int i = 0; i < I_SIZE; i++)
	{
		if (other._inventory[i])
			this->_inventory[i] = other._inventory[i]->clone();
		else
			this->_inventory[i] = NULL;
	}
	for (int i = 0; i < I_SIZE; i++)
		_floor[i] = NULL;
	_floorIndex = 0;
	return (*this);
}

/******************************************************************************/
/*								GETTERS										  */
/******************************************************************************/

std::string const& Character::getName() const
{
	return (this->_name);
}

/******************************************************************************/
/*								SETTERS										  */
/******************************************************************************/

void Character::setName(std::string const &name)
{
	this->_name = name;
}

/******************************************************************************/
/*							PUBLIC FUNCTIONS								  */
/******************************************************************************/

void Character::equip(AMateria* m)
{
	if (!m)
	{
		std::cout << PURPLE << "[E] " << _name
				  << " cannot equip a NULL Materia." << RESET << std::endl;
		return;
	}
	for (int i = 0; i < I_SIZE; i++)
	{
		if (this->_inventory[i] == NULL)
		{
			this->_inventory[i] = m;
			std::cout << PURPLE << this->_name
					  << " equips " << m->getType()
					  << " in slot " << i << RESET << std::endl;
			return;
		}
	}
	std::cout << PURPLE << "[E] " << this->_name << " cannot equip "
			  << m->getType() << " (inventory full)" << RESET << std::endl;
	delete m;
}


void Character::unequip(int idx)
{
	if (idx < 0 || idx >= I_SIZE || !_inventory[idx])
	{
		std::cout << PURPLE << "[E] " << _name
				  << " cannot unequip Materia at slot " << idx
				  << " (invalid or empty slot)." << RESET << std::endl;
		return;
	}
	if (this->_inventory[idx] == NULL)
		return;
	std::cout << PURPLE << this->_name << " unequips Materia at slot "
			  << idx << RESET << std::endl;
	_floor[_floorIndex++] = _inventory[idx];
	_inventory[idx] = NULL;
}


void Character::use(int idx, ICharacter& target)
{
	if (idx < 0 || idx >= I_SIZE || !_inventory[idx])
	{
		std::cout << PURPLE << "[E] " << this->_name 
				  << " tried to use Materia at slot " << idx 
				  << " but it's invalid or empty." << RESET << std::endl;
		return;
	}
	this->_inventory[idx]->use(target);
}
