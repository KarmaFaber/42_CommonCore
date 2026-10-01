/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FragTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 22:43:58 by mzolotar          #+#    #+#             */
/*   Updated: 2025/09/25 08:47:28 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRAGTRAP_HPP
#define FRAGTRAP_HPP

#include "ClapTrap.hpp"

class FragTrap : virtual public ClapTrap {
	public:
		FragTrap(void);
		FragTrap(std::string name);
		FragTrap (const FragTrap& other);
		FragTrap& operator=(const FragTrap& other);
		~FragTrap();

		unsigned int	getAttackDamageDefault( void ) const;
		unsigned int	getHitPointsDefault( void ) const;

		void			highFivesGuys(void);
};

#endif