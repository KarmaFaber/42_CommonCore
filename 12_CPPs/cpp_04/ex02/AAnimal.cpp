/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AAnimal.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 20:32:17 by mzolotar          #+#    #+#             */
/*   Updated: 2025/10/28 09:54:16 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AAnimal.hpp"

/******************************************************************************/
/*						CONSTRUCTORS & DESTRUCTORS							  */
/******************************************************************************/
/*	Default Constructor		*/
AAnimal::AAnimal(void)
		  : type("AAnimal")
{
	std::cout << CYELLOW << D_C_ANIMAL << CRESET << std::endl;
}

/*	Atribute Constructor	*/
AAnimal::AAnimal(std::string type)
		  : type(type)
{
	std::cout << CYELLOW << A_C_ANIMAL << CRESET << std::endl;
}

/*	Copy Constructor		*/
AAnimal::AAnimal(const AAnimal& other)
		  : type(other.type)
{
	std::cout << CYELLOW << C_C_ANIMAL << CRESET << std::endl;
}

/*	Desctructor				*/
AAnimal::~AAnimal()
{
	std::cout << CYELLOW << D_ANIMAL << CRESET << std::endl;
}

/******************************************************************************/
/*								OPERATORS								  	  */
/******************************************************************************/
/*	Copy Assignment Operator	*/
AAnimal& AAnimal::operator=(const AAnimal& other)
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

std::string	AAnimal::getType( void ) const
{
	return (type);
}

/******************************************************************************/
/*								SETTERS										  */
/******************************************************************************/

void	AAnimal::setType (std::string type)
{
	this->type = type;
}

/******************************************************************************/
/*							PUBLIC FUNCTIONS								  */
/******************************************************************************/

void	AAnimal::makeSound() const
{
	std::cout << CYELLOW << ANIMAL_SOUND << CRESET << std::endl;
}
