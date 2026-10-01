/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanB.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 11:46:14 by mzolotar          #+#    #+#             */
/*   Updated: 2025/09/04 09:20:28 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HUMANB_HPP
# define HUMANB_HPP

#include <string>
#include <iostream>
#include "Weapon.hpp"

# define CGREEN	"\033[0;32m"
# define CRESET	"\033[0m"

class HumanB {
	private:
		std::string	_name_b;
		Weapon*		_weapon_b;

	public:
		HumanB (const std::string& str_name_b);
		~HumanB ();

		void	setWeapon(Weapon& weapon_b);
		void	attack(void) const;
};

#endif
