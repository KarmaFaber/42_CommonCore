/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AAnimal.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 20:32:38 by mzolotar          #+#    #+#             */
/*   Updated: 2025/10/17 09:54:24 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANIMAL_HPP
# define ANIMAL_HPP

#include "header.h"
#include <iostream>
#include <string>
#include <cstring>

class AAnimal
{
	protected:
		std::string		type;
	public:
		AAnimal( void );
		AAnimal(std::string type);
		AAnimal(const AAnimal& other);
		virtual ~AAnimal();

		//Copy Assignment Operator
		AAnimal& operator=(const AAnimal& other);

		//getters & setters
		std::string		getType( void ) const;
		void			setType(std::string type);

		//pure abstract method:
		virtual void	makeSound() const = 0;
};

#endif
