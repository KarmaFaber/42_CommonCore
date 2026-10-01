/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 20:32:44 by mzolotar          #+#    #+#             */
/*   Updated: 2025/10/28 08:50:35 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAT_HPP
# define CAT_HPP

#include "Animal.hpp"
#include "header.h"
#include "Brain.hpp"

class Cat : public Animal
{
	private:
		Brain*	brain;
		
	public:
		Cat(void);
		Cat(std::string type);
		Cat(const Cat& other);
		~Cat();
		
		Cat&	operator=(const Cat& other);
		
		//Brain getter:
		Brain*	getBrain() const;
		
		void	makeSound() const;
};

#endif
