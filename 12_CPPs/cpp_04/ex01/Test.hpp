/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Test.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 22:45:50 by mzolotar          #+#    #+#             */
/*   Updated: 2025/10/17 11:00:27 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_HPP
#define TEST_HPP

#include <iostream>
#include <ostream>
#include <cstring>

#include "header.h"

#include "Animal.hpp"
#include "Brain.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"

class Test
{
	public:
		static void	testOverwrite();
		static void	testPolymorphism();
		static void	testPolymorphismDog();
		static void	testOverwriteWrongAnimal();
		static void	testPolymorphismWrongCat();
		static void	testWrongPolymorphism();
};

void	showMsg(const char* color, const char* msg, const char* reset);

#endif
