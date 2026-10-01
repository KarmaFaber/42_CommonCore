/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Brain.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 09:28:39 by mzolotar          #+#    #+#             */
/*   Updated: 2025/10/17 11:55:54 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BRAIN_HPP
#define BRAIN_HPP

# define BRAIN_IDEAS		100

#include "header.h"
#include <ostream>
#include <iostream>
#include <cstdlib>

class Brain
{
	private:
		std::string	ideas[BRAIN_IDEAS];

	public:
		Brain( void );
		Brain(const Brain& other);
		~Brain();

		//Copy Assignment Operator
		Brain& operator=(const Brain& other);
		
		//getters & setters
		std::string		getIdea(int idx) const;
		void			setIdea(int idx, const std::string& idea);
		void			RandomIdeas();
};

#endif