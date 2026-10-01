/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 20:32:41 by mzolotar          #+#    #+#             */
/*   Updated: 2025/10/28 08:52:57 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cat.hpp"

/******************************************************************************/
/*						CONSTRUCTORS & DESTRUCTORS							  */
/******************************************************************************/
/*	Default Constructor		*/
Cat::Cat(void)
		  : AAnimal("Cat"),
			brain (new Brain())
{
	std::cout << CCYAN << D_C_CAT << CRESET << std::endl;
}

/*	Atribute Constructor	*/
Cat::Cat(std::string type)
		  : AAnimal(type),
			brain (new Brain())
{
	std::cout << CCYAN << A_C_CAT << CRESET << std::endl;
}

/*	Copy Constructor		*/
Cat::Cat(const Cat& other) 
		  : AAnimal(other),
			brain(new Brain(*other.brain))
{
	std::cout << CCYAN << A_C_CAT << CRESET << std::endl;
}

/*	Desctructor				*/
Cat::~Cat()
{
	delete brain;
	std::cout << CCYAN << D_CAT << CRESET << std::endl;
}

/******************************************************************************/
/*								OPERATORS								  	  */
/******************************************************************************/
/*	Copy Assignment Operator	*/
Cat& Cat::operator=(const Cat& other)
{
	std::cout << CCYAN << C_O_CAT << CRESET << std::endl;
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
Brain* Cat::getBrain() const
{
	return (brain);
}

/******************************************************************************/
/*							PUBLIC FUNCTIONS								  */
/******************************************************************************/

void Cat::makeSound() const
{
	std::cout << CCYAN << CAT_SOUND << CRESET << std::endl;
}
