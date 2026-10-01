/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 19:00:03 by mzolotar          #+#    #+#             */
/*   Updated: 2025/09/01 20:47:40 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_HPP
#define FIXED_HPP

#include <iostream>

class Fixed{
	private:
		int					_raw;
		static const int	_fractionalBits = 8;

	public:
		Fixed(void);								// Default Constructor
		Fixed(const Fixed& other);					// Copy Constructor
		Fixed& operator = (const Fixed& other);		// Copy Assignment Operator
		~Fixed();									// Destructor
		
		int getRawBits( void ) const;
		void setRawBits( int const raw );
};

#endif
