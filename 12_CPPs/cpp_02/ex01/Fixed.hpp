/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 19:00:03 by mzolotar          #+#    #+#             */
/*   Updated: 2025/09/02 23:20:04 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_HPP
#define FIXED_HPP

#include <iostream>
#include <cmath>

# define CRED "\033[0;31m"
# define CBLACK "\033[0;30m"
# define CBLUE "\033[0;34m"
# define CGREEN  "\033[0;32m"
# define CRESET "\033[0m"

class Fixed{
	private:
		int					_raw;
		static const int	_fractionalBits = 8;

	public:
		Fixed( void );								// Default Constructor
		Fixed( const int int_num );					// Constructor
		Fixed( const float f_num );					// Constructor
		Fixed( const Fixed& other );				// Copy Constructor

		Fixed& operator = ( const Fixed& other) ;	// Copy Assignment Operator
		~Fixed();									// Destructor
		
		int		getRawBits( void ) const;
		void	setRawBits( int const raw );

		float	toFloat( void ) const;
		int		toInt( void ) const;
};

std::ostream& operator<< ( std::ostream& os, const Fixed& number );

#endif
