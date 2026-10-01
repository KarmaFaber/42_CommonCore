/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 08:04:10 by mzolotar          #+#    #+#             */
/*   Updated: 2025/09/25 08:30:05 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLAPTRAP_HPP
#define CLAPTRAP_HPP

# define CRED		"\033[0;31m"
# define CBLACK		"\033[0;30m"
# define CBLUE		"\033[0;34m"
# define CGREEN		"\033[0;32m"
# define CYELLOW	"\033[0;33m"
# define CMAGENTA	"\033[0;35m"
# define CCYAN		"\033[0;36m"
# define CRESET		"\033[0m"

#include <iostream>
#include <cstring>

class ClapTrap {
	private:
		std::string		_name;
		int				_hit_points;
		int				_energy_points;
		int				_attack_damage;

	public:
		ClapTrap(void);
		ClapTrap( std::string name );
		ClapTrap ( const ClapTrap& other );
		ClapTrap& operator=( const ClapTrap& other );
		virtual ~ClapTrap();

		//getters:
		std::string		getName( void ) const;
		unsigned int	getHitPoints( void ) const;
		unsigned int	getEnergyPoints( void ) const;
		unsigned int	getAttackDamage( void ) const;

		//setters:
		void			setName(std::string name);
		void			setHitPoints(int hp);
		void			setEnergyPoints(int ep);
		void			setAttackDamage(int ad);

		//public methods:
		void			attack(const std::string& target);
		void			takeDamage(unsigned int amount);
		void			beRepaired(unsigned int amount);
};

#endif
