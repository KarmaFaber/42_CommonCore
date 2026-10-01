/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 20:32:52 by mzolotar          #+#    #+#             */
/*   Updated: 2025/10/28 09:56:54 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOG_HPP
# define DOG_HPP

#include "AAnimal.hpp"
#include "header.h"
#include "Brain.hpp"

class Dog : public AAnimal
{
	private:
		Brain*	brain;
	public:
		Dog(void);
		Dog (std::string type);
		Dog(const Dog& other);
		~Dog();
		
		Dog&	operator=(const Dog& other);

		//Brain getter:
		Brain*	getBrain() const;

		void	makeSound() const;
};

#endif
