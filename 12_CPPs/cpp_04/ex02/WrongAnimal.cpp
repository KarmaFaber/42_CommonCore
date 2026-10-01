/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongAnimal.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 20:33:06 by mzolotar          #+#    #+#             */
/*   Updated: 2025/10/28 09:55:11 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "WrongAnimal.hpp"

/******************************************************************************/
/*						CONSTRUCTORS & DESTRUCTORS							  */
/******************************************************************************/
/*	Default Constructor		*/
WrongAnimal::WrongAnimal(void)
		  : type("WrongAnimal")
{
	std::cout << CYELLOW << D_C_WRONG_ANIMAL << CRESET << std::endl;
}

/*	Atribute Constructor	*/
WrongAnimal::WrongAnimal(std::string type)
		  : type(type)
{
	std::cout << CYELLOW << A_C_WRONG_ANIMAL << CRESET << std::endl;
}

/*	Copy Constructor		*/
WrongAnimal::WrongAnimal(const WrongAnimal& other)
		  : type(other.type)
{
	std::cout << CYELLOW << C_C_WRONG_ANIMAL << CRESET << std::endl;
}

/*	Desctructor				*/
WrongAnimal::~WrongAnimal()
{
	std::cout << CYELLOW << D_WRONG_ANIMAL << CRESET << std::endl;
}

/******************************************************************************/
/*								OPERATORS								  	  */
/******************************************************************************/
/*	Copy Assignment Operator	*/
WrongAnimal& WrongAnimal::operator=(const WrongAnimal& other)
{
	std::cout << CYELLOW << C_O_WRONG_ANIMAL << CRESET << std::endl;
	if (this != &other)
	{
		this->type = other.type;
	}
	return (*this);
}

/******************************************************************************/
/*								GETTERS										  */
/******************************************************************************/

std::string	WrongAnimal::getType( void ) const
{
	return (type);
}

/******************************************************************************/
/*								SETTERS										  */
/******************************************************************************/

void	WrongAnimal::setType (std::string type)
{
	this->type = type;
}

/******************************************************************************/
/*							PUBLIC FUNCTIONS								  */
/******************************************************************************/

void	WrongAnimal::makeSound() const
{
	std::cout << CYELLOW << WRONG_ANIMAL_SOUND << CRESET << std::endl;
}
