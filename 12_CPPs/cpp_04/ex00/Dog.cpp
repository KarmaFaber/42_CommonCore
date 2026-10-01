/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 20:32:48 by mzolotar          #+#    #+#             */
/*   Updated: 2025/10/28 09:47:28 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Dog.hpp"

/******************************************************************************/
/*						CONSTRUCTORS & DESTRUCTORS							  */
/******************************************************************************/
/*	Default Constructor		*/
Dog::Dog(void)
		  : Animal("Dog")
{
	std::cout << CGREEN << D_C_DOG << CRESET << std::endl;
}

/*	Atribute Constructor	*/
Dog::Dog (std::string type)
		  : Animal(type)
{
	std::cout << CGREEN << A_C_DOG << CRESET << std::endl;
}

/*	Copy Constructor		*/
Dog::Dog(const Dog& other) 
		  : Animal(other)
{
	std::cout << CGREEN << A_C_DOG << CRESET << std::endl;
}

/*	Desctructor				*/
Dog::~Dog()
{
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
		Animal::operator=(other);
	}
	return (*this);
}

/******************************************************************************/
/*							PUBLIC FUNCTIONS								  */
/******************************************************************************/

void Dog::makeSound() const
{
	std::cout << CGREEN << DOG_SOUND << CRESET << std::endl;
}
