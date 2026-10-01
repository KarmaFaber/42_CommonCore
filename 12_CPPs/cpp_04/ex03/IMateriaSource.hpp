/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IMateriaSource.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 12:57:54 by mzolotar          #+#    #+#             */
/*   Updated: 2025/10/27 12:23:09 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef I_MATERIA_SOURCE_HPP
#define I_MATERIA_SOURCE_HPP

#include <string>
#include <iostream>
#include "AMateria.hpp"
#include "header.h"
#include "Colors.h"

class IMateriaSource
{
	public:
		virtual			~IMateriaSource() {}
		virtual void	learnMateria(AMateria *materia) = 0;
		virtual			AMateria* createMateria(std::string const &type) = 0;
};

#endif
