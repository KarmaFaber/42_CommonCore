/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 18:59:53 by mzolotar          #+#    #+#             */
/*   Updated: 2025/09/25 12:35:10 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

/******************************************************************************/
/*						CONSTRUCTORS & DESTRUCTORS							  */
/******************************************************************************/

/*	Default Constructor			*/
Fixed::Fixed(void)
		  : _raw(0)
{
	std::cout << "Default Constructor called" << std::endl;
}

/*	Copy Constructor			*/
Fixed::Fixed(const Fixed& other)
		  : _raw(other._raw)
{
	std::cout << "Copy Constructor called" << std::endl;
}

/*	Constructor from integer	*/
Fixed::Fixed(const int int_num)
		  : _raw(int_num << _fractionalBits)
{
	std::cout << "Int Constructor called" << std::endl;
}

/*	Constructor from float		*/
Fixed::Fixed(const float f_num)
		  : _raw(static_cast<int>(f_num * (1 << _fractionalBits)
		  + (f_num >= 0 ? 0.5f : -0.5f)))
{
	std::cout << "Float Constructor called" << std::endl;
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
Fixed& Fixed::operator=(const Fixed& other)
{
	std::cout << "Copy Assignment Operator called" << std::endl;
	if (this != &other)
	{
		this->_raw = other._raw;
	}
	return (*this);
}

/*	comparison operators -> x6:	*/
bool Fixed::operator>(const Fixed& other) const
{
	return (this->_raw > other._raw);
}

bool Fixed::operator<(const Fixed& other) const
{
	return (this->_raw < other._raw);
}

bool Fixed::operator>=(const Fixed& other) const
{
	return (this->_raw >= other._raw);
}

bool Fixed::operator<=(const Fixed& other) const
{
	return (this->_raw <= other._raw);
}

bool Fixed::operator==(const Fixed& other) const
{
	return (this->_raw == other._raw);
}

bool Fixed::operator!=(const Fixed& other) const
{
	return (this->_raw != other._raw);
}

/*	arithmetic operators -> x4	*/
Fixed Fixed::operator+(const Fixed& other) const
{
	Fixed result;
	result.setRawBits(this->_raw + other._raw);
	return (result);
}

Fixed Fixed::operator-(const Fixed& other) const
{
	Fixed result;
	result.setRawBits(this->_raw - other._raw);
	return (result);
}

Fixed Fixed::operator*(const Fixed& other) const
{
	return (Fixed(this->toFloat() * other.toFloat()));
}

Fixed Fixed::operator/(const Fixed& other) const
{
	if (other.getRawBits() == 0)
	{
		std::cerr << "Error: division by zero" << std::endl;
		return (Fixed(0));
	}
	return (Fixed(this->toFloat() / other.toFloat()));
}

/*	increment/decrement operators	*/
//pre-increment
Fixed& Fixed::operator++()
{
	++_raw;
	return (*this);
}

//post-increment
Fixed Fixed::operator++(int)
{
	Fixed temp = *this;
	++(*this);
	return (temp);
}

//pre-decrement
Fixed& Fixed::operator--()
{
	--_raw;
	return (*this);
}

//post-decrement
Fixed Fixed::operator--(int)
{
	Fixed temp = *this;
	--(*this);
	return (temp);
}

/******************************************************************************/
/*								GETTERS										  */
/******************************************************************************/

int Fixed::getRawBits( void ) const
{
	std::cout << "getRawBits member function called" << std::endl;
	return (this->_raw);
}

/******************************************************************************/
/*								SETTERS										  */
/******************************************************************************/

void Fixed::setRawBits( int const raw )
{
	this->_raw = raw;
	std::cout << "setRawBits member function called" << std::endl;
}

/******************************************************************************/
/*							PUBLIC FUNCTIONS								  */
/******************************************************************************/

/*	Converts fixed-point to float	*/
float Fixed::toFloat(void) const
{
	return ((float) this->_raw / (1 << _fractionalBits));
}

/*	Converts fixed-point to int		*/
int Fixed::toInt(void) const
{
	return (this->_raw >> _fractionalBits);
}

/*	Min & Max functions				*/
Fixed& Fixed::min(Fixed& a, Fixed& b)
{
	if (a < b)
		return a;
	return b;
}

const Fixed& Fixed::min(const Fixed& a, const Fixed& b)
{
	if (a < b)
		return a;
	return b;
}

Fixed& Fixed::max(Fixed& a, Fixed& b)
{
	if (a > b)
		return a;
	return b;
}

const Fixed& Fixed::max(const Fixed& a, const Fixed& b)
{
	if (a > b)
		return a;
	return b;
}

/******************************************************************************/
/*							GLOBAL FUNCTIONS								  */
/******************************************************************************/

std::ostream& operator<<( std::ostream& os, const Fixed& number )
{
	os << number.toFloat();
	return ( os );
}
