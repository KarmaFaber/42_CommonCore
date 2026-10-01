/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Character.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 12:57:18 by mzolotar          #+#    #+#             */
/*   Updated: 2025/10/28 10:05:21 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#define I_SIZE 4

# include "AMateria.hpp"
# include "ICharacter.hpp"
#include "header.h"
#include "Colors.h"
# include <string>
#include <iostream>

class Character : public ICharacter
{
	private:
		std::string			_name;
		AMateria*			_inventory[I_SIZE];

		AMateria*			_floor[100];
		int					_floorIndex;

	public:
		Character(void);
		Character(std::string const& name);
		Character(const Character& other);
		Character& operator=(const Character& other);
		~Character();

		std::string const&	getName() const;
		
		void	setName(std::string const &name);

		void	equip(AMateria* m);
		void	unequip(int idx);
		void	use(int idx, ICharacter& target);
};

#endif
