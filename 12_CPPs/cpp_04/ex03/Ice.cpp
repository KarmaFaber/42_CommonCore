/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ice.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 12:57:34 by mzolotar          #+#    #+#             */
/*   Updated: 2025/10/28 09:23:06 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Ice.hpp"
//#include "ICharacter.hpp"

/******************************************************************************/
/*						CONSTRUCTORS & DESTRUCTORS							  */
/******************************************************************************/
/*	Default Constructor		*/
Ice::Ice(void)
		  : AMateria("ice")
{
	std::cout << BLUE << ICE_DEF_CTOR << RESET << std::endl;
}

/*	Copy Constructor		*/
Ice::Ice(const Ice& other)
		  : AMateria(other)
{
	std::cout << BLUE << ICE_COPY_CTOR << RESET << std::endl;
}

/*	Desctructor				*/
Ice::~Ice()
{
	std::cout << BLUE << ICE_DTOR << RESET << std::endl;
}


/******************************************************************************/
/*								OPERATORS								  	  */
/******************************************************************************/

/*	Copy Assignment Operator	*/
Ice& Ice::operator=(const Ice& other)
{
	std::cout << BLUE << ICE_ASS_OP << RESET << std::endl;
	if (this != &other)
	{
		AMateria::operator=(other);
	}
	return (*this);
}

/******************************************************************************/
/*							PUBLIC FUNCTIONS								  */
/******************************************************************************/

AMateria* Ice::clone() const
{
	return (new Ice(*this));
}

void Ice::use(ICharacter& target)
{
	std::cout << BLUE << ICE_MSG << target.getName() << ICE_END << RESET << std::endl;
}
