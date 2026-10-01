/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongCat.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 07:58:19 by mzolotar          #+#    #+#             */
/*   Updated: 2025/10/28 09:50:37 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef WRONG_CAT_HPP
# define WRONG_CAT_HPP

#include "WrongAnimal.hpp"
#include "header.h"
#include "Brain.hpp"

class WrongCat : public WrongAnimal
{
	private:
		Brain*	brain;
	public:
		WrongCat(void);
		WrongCat (std::string type);
		WrongCat(const WrongCat& other);
		~WrongCat();

		//Brain getter:
		Brain*	getBrain() const;
		
		WrongCat&	operator=(const WrongCat& other);
		void		makeSound() const;
};

#endif
