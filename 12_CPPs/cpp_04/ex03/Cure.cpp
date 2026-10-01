/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cure.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 12:57:22 by mzolotar          #+#    #+#             */
/*   Updated: 2025/10/28 10:04:33 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cure.hpp"

/******************************************************************************/
/*						CONSTRUCTORS & DESTRUCTORS							  */
/******************************************************************************/
/*	Default Constructor		*/
Cure::Cure(void)
		  : AMateria ("cure")
{
	std::cout << BLUE << CURE_DEF_CTOR << RESET << std::endl;
}

/*	Copy Constructor		*/
Cure::Cure( const Cure& other)
		  : AMateria (other)
{
	std::cout << BLUE << CURE_COPY_CTOR << RESET << std::endl;
}

/*	Desctructor				*/
Cure::~Cure()
{
	std::cout << BLUE << CURE_DTOR << RESET << std::endl;
}

/******************************************************************************/
/*								OPERATORS								  	  */
/******************************************************************************/
/*	Copy Assignment Operator	*/
Cure& Cure::operator=(const Cure& other)
{
	std::cout << BLUE << CURE_ASS_OP << RESET << std::endl;
	if (this != &other)
	{
		AMateria::operator=(other);
	}
	return (*this);
}

/******************************************************************************/
/*							PUBLIC FUNCTIONS								  */
/******************************************************************************/

AMateria* Cure::clone() const
{
	return (new Cure(*this));
}

void Cure::use(ICharacter& target)
{
	std::cout << BLUE << CURE_MSG << target.getName() << CURE_END << RESET << std::endl;
}
