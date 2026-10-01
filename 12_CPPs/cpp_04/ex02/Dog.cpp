/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 20:32:48 by mzolotar          #+#    #+#             */
/*   Updated: 2025/10/28 08:53:01 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Dog.hpp"

/******************************************************************************/
/*						CONSTRUCTORS & DESTRUCTORS							  */
/******************************************************************************/
/*	Default Constructor		*/
Dog::Dog(void)
		  : AAnimal("Dog"),
			brain (new Brain())
{
	std::cout << CGREEN << D_C_DOG << CRESET << std::endl;
}

/*	Atribute Constructor	*/
Dog::Dog(std::string type)
		  : AAnimal(type),
			brain (new Brain())
{
	std::cout << CGREEN << A_C_DOG << CRESET << std::endl;
}

/*	Copy Constructor		*/
Dog::Dog(const Dog& other)
		  : AAnimal(other),
			brain(new Brain(*other.brain))
{
	std::cout << CGREEN << A_C_DOG << CRESET << std::endl;
}

/*	Desctructor				*/
Dog::~Dog()
{
	delete brain;
	std::cout << CGREEN << D_DOG << CRESET << std::endl;
}

/******************************************************************************/
/*								OPERATORS								  	  */
/******************************************************************************/
/*	Copy Assignment Operator	*/
Dog& Dog::operator=(const Dog& other)
{
	std::cout << CGREEN << C_O_DOG << CRESET << std::endl;
	if (this != &other)
	{
		AAnimal::operator=(other);
		*brain = *other.brain;
	}
	return (*this);
}

/******************************************************************************/
/*								GETTERS										  */
/******************************************************************************/

Brain* Dog::getBrain() const
{
	return (brain);
}

/******************************************************************************/
/*							PUBLIC FUNCTIONS								  */
/******************************************************************************/

void Dog::makeSound() const
{
	std::cout << CGREEN << DOG_SOUND << CRESET << std::endl;
}
