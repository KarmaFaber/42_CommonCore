/* ************************************************************************** */
/*	                                                                        */
/*                                                        :::      ::::::::   */
/*   Cure.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 12:57:26 by mzolotar          #+#    #+#             */
/*   Updated: 2025/09/25 13:31:48 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CURE_HPP
#define CURE_HPP

#include "AMateria.hpp"
#include "header.h"
#include "Colors.h"

class Cure : public AMateria
{
	private:

	public:
		Cure(void);
		Cure(const Cure& other);
		Cure& operator=(const Cure& other);
		~Cure();
		
		AMateria*	clone() const;
		void	use(ICharacter& target);
};
#endif
