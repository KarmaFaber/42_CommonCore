/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongCat.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 07:58:31 by mzolotar          #+#    #+#             */
/*   Updated: 2025/10/28 09:55:00 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "WrongCat.hpp"

/******************************************************************************/
/*						CONSTRUCTORS & DESTRUCTORS							  */
/******************************************************************************/
/*	Default Constructor		*/
WrongCat::WrongCat(void)
		  : WrongAnimal("WrongCat"),
			brain (new Brain())
{
	std::cout << CCYAN << D_C_WRONG_CAT << CRESET << std::endl;
}

/*	Atribute Constructor	*/
WrongCat::WrongCat (std::string type)
		  : WrongAnimal(type),
			brain (new Brain())
{
	std::cout << CCYAN << A_C_WRONG_CAT << CRESET << std::endl;
}

/*	Copy Constructor		*/
WrongCat::WrongCat(const WrongCat& other) 
		  : WrongAnimal(other),
			brain(new Brain(*other.brain))
{
	std::cout << CCYAN << C_C_WRONG_CAT << CRESET << std::endl;
}

/*	Desctructor				*/
WrongCat::~WrongCat()
{
	delete brain;
	std::cout << CCYAN << D_WRONG_CAT << CRESET << std::endl;
}

/******************************************************************************/
/*								OPERATORS								  	  */
/******************************************************************************/
/*	Copy Assignment Operator	*/
WrongCat& WrongCat::operator=(const WrongCat& other)
{
	std::cout << CCYAN << C_O_WRONG_CAT << CRESET << std::endl;
	if (this != &other)
	{
		WrongAnimal::operator=(other);
		*brain = *other.brain;
	}
	return (*this);
}
/******************************************************************************/
/*								GETTERS										  */
/******************************************************************************/

Brain* WrongCat::getBrain() const
{
	return (brain);
}

/******************************************************************************/
/*							PUBLIC FUNCTIONS								  */
/******************************************************************************/

void WrongCat::makeSound() const
{
	std::cout << CCYAN << WRONG_CAT_SOUND << CRESET << std::endl;
}
