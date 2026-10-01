/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Harl.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 13:39:39 by mzolotar          #+#    #+#             */
/*   Updated: 2025/09/04 09:25:36 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HARL_HPP
# define HARL_HPP

#include <iostream>

# define DEBUG		"[DEBUG]\nI love having extra bacon for my " \
					"7XL-double-cheese-triple-pickle-special-ketchup burger.\n" \
					"I really do!"

# define INFO		"[INFO]\nI cannot believe adding extra bacon costs more money.\n" \
					"You didn’t put enough bacon in my burger!\n" \
					"If you did, I wouldn’t be asking for more!"

# define WARNING	"[WARNING]\nI think I deserve to have some extra bacon for free.\n" \
					"I’ve been coming for years whereas you started working here " \
					"since last month."

# define ERROR		"[ERROR]\nThis is unacceptable! I want to speak to the manager now."

# define CRED		"\033[0;31m"
# define CBLUE		"\033[0;34m"
# define CGREEN		"\033[0;32m"
# define CRESET		"\033[0m"

class Harl
{
	private:
		void	debug( void );
		void	info( void );
		void	warning( void );
		void	error( void );

	public:
		Harl(void);
		~Harl();
		void	complain( std::string level );
};

#endif