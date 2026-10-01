/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 19:00:03 by mzolotar          #+#    #+#             */
/*   Updated: 2025/09/25 12:25:58 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_HPP
#define FIXED_HPP

#include <iostream>
#include <cmath>

class Fixed{
	private:
		int					_raw;
		static const int	_fractionalBits = 8;

	public:
		Fixed(void);								// Default Constructor
		Fixed(const Fixed& other);				// Copy Constructor
		Fixed& operator=(const Fixed& other) ;		// Copy Assignment Operator
		~Fixed();									// Destructor

		Fixed(const int int_num);					// Constructor from integer
		Fixed(const float f_num);					// Constructor from float
		
		int		getRawBits(void) const;
		void	setRawBits(int const raw);

		float	toFloat(void) const;
		int		toInt(void) const;
		
		/* Comparison operators (x6) */
		bool	operator>(const Fixed& other) const;
		bool	operator<(const Fixed& other) const;
		bool	operator>=(const Fixed& other) const;
		bool	operator<=(const Fixed& other) const;
		bool	operator==(const Fixed& other) const;
		bool	operator!=(const Fixed& other) const;

		/* Arithmetic operators (x4) */
		Fixed	operator+(const Fixed& other) const;
		Fixed	operator-(const Fixed& other) const;
		Fixed	operator*(const Fixed& other) const;
		Fixed	operator/(const Fixed& other) const;

		//increment/decrement operators:
		//pre-increment
		Fixed&	operator++();
		//post-increment
		Fixed	operator++(int);
		//pre-decrement
		Fixed&	operator--();
		//post-decrement
		Fixed	operator--(int);

		// x4 ->min && max
		static	Fixed& min(Fixed& a, Fixed& b);
		static const	Fixed& min(const Fixed& a, const Fixed& b);
		static	Fixed& max(Fixed& a, Fixed& b);
		static const	Fixed& max(const Fixed& a, const Fixed& b);
};

		std::ostream&	operator<< ( std::ostream& os, const Fixed& number );

#endif
