/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ICharacter.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 12:41:22 by mzolotar          #+#    #+#             */
/*   Updated: 2025/10/28 10:07:42 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef I_CHARACTER_HPP
#define I_CHARACTER_HPP

#include <string>
#include <iostream>
#include "AMateria.hpp"
#include "header.h"
#include "Colors.h"

class AMateria;

class ICharacter
{
	public:
		virtual ~ICharacter() {}

		virtual std::string const & getName() const = 0;

		virtual void	equip(AMateria* m) = 0;
		virtual void	unequip(int idx) = 0;
		virtual void	use(int idx, ICharacter& target) = 0;
};

#endif
