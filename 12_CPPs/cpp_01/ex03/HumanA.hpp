/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanA.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 11:46:06 by mzolotar          #+#    #+#             */
/*   Updated: 2025/09/04 09:20:01 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HUMANA_HPP
# define HUMANA_HPP

#include <string>
#include <iostream>
#include "Weapon.hpp"

# define CGREEN	"\033[0;32m"
# define CRESET	"\033[0m"

class HumanA
{
	private:
		std::string	_name_a;
		Weapon&		_weapon_a;

	public:
		HumanA (const std::string& _str_name_a, Weapon& _str_weapon_a);
		~HumanA ();

		void	attack(void) const;
};

#endif
