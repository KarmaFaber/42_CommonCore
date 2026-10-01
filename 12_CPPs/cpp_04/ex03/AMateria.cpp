/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AMateria.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 12:37:49 by mzolotar          #+#    #+#             */
/*   Updated: 2025/10/28 09:19:43 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AMateria.hpp"

/******************************************************************************/
/*						CONSTRUCTORS & DESTRUCTORS							  */
/******************************************************************************/
/*	Default Constructor		*/
AMateria::AMateria(void)
		  :_type("default_type")
{
	std::cout << YELLOW << AMAT_DEF_CTOR << RESET << std::endl;
}

/*	Atribute Constructor	*/
AMateria::AMateria(std::string const &type)
		: _type(type)
{
	std::cout << YELLOW << AMAT_ARG_CTOR << RESET << std::endl;
}

/*	Copy Constructor		*/
AMateria::AMateria(AMateria const& other)
		  : _type(other._type)
{
	std::cout << YELLOW << AMAT_COPY_CTOR << RESET << std::endl;
}

/*	Desctructor				*/
AMateria::~AMateria()
{
	std::cout << YELLOW << AMAT_DTOR << RESET << std::endl;
}

/******************************************************************************/
/*								OPERATORS								  	  */
/******************************************************************************/
/*	Copy Assignment Operator	*/
AMateria& AMateria::operator=(const AMateria& other)
{
	std::cout << YELLOW << AMAT_ASS_OP << RESET << std::endl;
	if (this != &other)
	{
		this->_type = other._type;
	}
	return (*this);
}

/******************************************************************************/
/*								GETTERS										  */
/******************************************************************************/

std::string const & AMateria::getType() const 
{
	return (this->_type);
}

/******************************************************************************/
/*							PUBLIC FUNCTIONS								  */
/******************************************************************************/

void AMateria::use(ICharacter& target)
{
	(void)target;
}
