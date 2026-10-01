/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 20:32:44 by mzolotar          #+#    #+#             */
/*   Updated: 2025/10/28 09:47:18 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAT_HPP
# define CAT_HPP

#include "Animal.hpp"
#include "header.h"

class Cat : public Animal
{
	public:
		Cat(void);
		Cat (std::string type);
		Cat(const Cat& other);
		~Cat();
		
		Cat&	operator=(const Cat& other);
		void	makeSound() const;
};

#endif
