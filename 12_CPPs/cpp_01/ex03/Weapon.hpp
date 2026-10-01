/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Weapon.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 11:46:22 by mzolotar          #+#    #+#             */
/*   Updated: 2025/09/04 09:20:50 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEAPON_HPP
# define WEAPON_HPP

#include <string>
#include <iostream>

# define CGREEN	"\033[0;32m"
# define CRESET	"\033[0m"

class Weapon{
	private:
		std::string	_type;

	public:
		Weapon (const std::string& str_type);
		~Weapon ();

		const std::string&	getType(void) const;
		void				setType(const std::string& str_type);
};

#endif