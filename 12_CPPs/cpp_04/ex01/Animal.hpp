/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 20:32:38 by mzolotar          #+#    #+#             */
/*   Updated: 2025/10/17 09:44:43 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANIMAL_HPP
# define ANIMAL_HPP

#include "header.h"
#include <iostream>
#include <string>
#include <cstring>

class Animal
{
	protected:
		std::string		type;
	public:
		Animal( void );
		Animal(std::string type);
		Animal(const Animal& other);
		virtual ~Animal();

		//Copy Assignment Operator
		Animal& operator=(const Animal& other);

		//getters & setters
		std::string		getType( void ) const;
		void			setType(std::string type);

		//public method:
		virtual void	makeSound() const;
};

#endif
