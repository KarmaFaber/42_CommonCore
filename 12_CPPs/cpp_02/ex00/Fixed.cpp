/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 18:59:53 by mzolotar          #+#    #+#             */
/*   Updated: 2025/09/25 10:07:34 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

/******************************************************************************/
/*						CONSTRUCTORS & DESTRUCTORS							  */
/******************************************************************************/

/*	Default Constructor	*/
Fixed::Fixed(void) : _raw(0)
{
	std::cout << "Default Constructor called" << std::endl;
}

/*	Copy Constructor	*/
Fixed::Fixed(const Fixed& other)
		  : _raw(other._raw)
{
	std::cout << "Copy Constructor called" << std::endl;
}

/*	Desctructor	*/
Fixed::~Fixed()
{
	std::cout << "Destructor called" << std::endl;
}

/******************************************************************************/
/*								OPERATORS								  	  */
/******************************************************************************/

/*	Copy Assignment Operator	*/
Fixed& Fixed::operator = (const Fixed& other)
{
	std::cout << "Copy assignment operator called" << std::endl;
	if (this != &other)
	{
		this->_raw=other._raw;
	}
	return (*this);
}

/******************************************************************************/
/*								GETTERS										  */
/******************************************************************************/

int Fixed::getRawBits( void ) const
{
	std::cout << "getRawBits member function called" << std::endl;
	return (_raw);
}

/******************************************************************************/
/*								SETTERS										  */
/******************************************************************************/

void Fixed::setRawBits( int const raw )
{
	_raw = raw;
	std::cout << "setRawBits member function called" << std::endl;
}
