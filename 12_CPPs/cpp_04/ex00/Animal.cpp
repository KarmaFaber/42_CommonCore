/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 20:32:17 by mzolotar          #+#    #+#             */
/*   Updated: 2025/10/28 09:46:33 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Animal.hpp"

/******************************************************************************/
/*						CONSTRUCTORS & DESTRUCTORS							  */
/******************************************************************************/
/*	Default Constructor		*/
Animal::Animal(void)
		  : type("Animal")
{
	std::cout << CYELLOW << D_C_ANIMAL << CRESET << std::endl;
}

/*	Atribute Constructor	*/
Animal::Animal(std::string type)
		  : type(type)
{
	std::cout << CYELLOW << A_C_ANIMAL << CRESET << std::endl;
}

/*	Copy Constructor		*/
Animal::Animal(const Animal& other)
		  : type(other.type)
{
	std::cout << CYELLOW << C_C_ANIMAL << CRESET << std::endl;
}

/*	Desctructor				*/
Animal::~Animal()
{
	std::cout << CYELLOW << D_ANIMAL << CRESET << std::endl;
}

/******************************************************************************/
/*								OPERATORS								  	  */
/******************************************************************************/
/*	Copy Assignment Operator	*/
Animal& Animal::operator=(const Animal& other)
{
	std::cout << CYELLOW << C_O_ANIMAL << CRESET << std::endl;
	if (this != &other)
	{
		this->type = other.type;
	}
	return (*this);
}

/******************************************************************************/
/*								GETTERS										  */
/******************************************************************************/

std::string	Animal::getType( void ) const
{
	return (type);
}

/******************************************************************************/
/*								SETTERS										  */
/******************************************************************************/

void	Animal::setType (std::string type)
{
	this->type = type;
}

/******************************************************************************/
/*							PUBLIC FUNCTIONS								  */
/******************************************************************************/

void	Animal::makeSound() const
{
	std::cout << CYELLOW << ANIMAL_SOUND << CRESET << std::endl;
}
