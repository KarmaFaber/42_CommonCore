/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MateriaSource.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 12:57:54 by mzolotar          #+#    #+#             */
/*   Updated: 2025/10/28 10:00:11 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATERIA_SOURCE_HPP
#define MATERIA_SOURCE_HPP

#define L_SIZE 4

#include <string>
#include <iostream>
#include "IMateriaSource.hpp"
#include "header.h"
#include "Colors.h"

class MateriaSource : public IMateriaSource
{
	private:
		AMateria			*_learnInventory[L_SIZE];

	public:
		MateriaSource(void);
		MateriaSource(const MateriaSource& other);
		MateriaSource& operator=(const MateriaSource& other);
		~MateriaSource();

		void		learnMateria(AMateria *materia);
		AMateria*	createMateria(std::string const &type);
};

#endif
