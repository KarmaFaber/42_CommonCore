/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongAnimal.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 20:33:19 by mzolotar          #+#    #+#             */
/*   Updated: 2025/10/28 09:55:05 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WRONG_ANIMAL_HPP
# define WRONG_ANIMAL_HPP

#include "header.h"
#include <iostream>
#include <string>
#include <cstring>

class WrongAnimal
{
	protected:
		std::string	type;
	public:
		WrongAnimal( void );
		WrongAnimal(std::string type);
		WrongAnimal(const WrongAnimal& other);
		~WrongAnimal();

		//Copy Assignment Operator
		WrongAnimal&	operator=(const WrongAnimal& other);

		//getters & setters
		std::string	getType( void ) const;
		void		setType(std::string type);

		//public method:
		void		makeSound() const;
};

#endif
