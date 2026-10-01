/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongCat.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 07:58:19 by mzolotar          #+#    #+#             */
/*   Updated: 2025/10/28 09:45:57 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WRONG_CAT_HPP
# define WRONG_CAT_HPP

#include "WrongAnimal.hpp"
#include "header.h"

class WrongCat : public WrongAnimal
{
	public:
		WrongCat( void );
		WrongCat (std::string type);
		WrongCat(const WrongCat& other);
		~WrongCat();

		WrongCat&	operator=(const WrongCat& other);
		void		makeSound() const;
};

#endif
