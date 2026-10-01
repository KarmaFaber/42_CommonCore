/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 09:34:23 by mzolotar          #+#    #+#             */
/*   Updated: 2025/09/04 09:18:03 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ZOMBIE_HPP
# define ZOMBIE_HPP

#include <string>
#include <iostream>

# define CRED	"\033[0;31m"
# define CBLACK	"\033[0;30m"
# define CBLUE	"\033[0;34m"
# define CGREEN	"\033[0;32m"
# define CRESET	"\033[0m"

class Zombie{
	private:
		std::string	_name;
	public:
		Zombie( void );
		Zombie( const std::string& input_name );
		~Zombie();
		void announce( void );
};

Zombie*	newZombie( std::string str_name );
void	randomChump( std::string str_name );

#endif