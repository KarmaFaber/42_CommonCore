/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Test.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 22:45:50 by mzolotar          #+#    #+#             */
/*   Updated: 2025/10/28 09:58:36 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_HPP
#define TEST_HPP

#include <iostream>
#include <ostream>
#include "Character.hpp"
#include "Cure.hpp"
#include "Ice.hpp"
#include "MateriaSource.hpp"
#include "header.h"
#include "Colors.h"

class Test
{
	public:
		//Subject Test:
		static void	testSubject(void);

		//General Errors:
		static void	instantiateAbstactcClass(void);
		static void	testPolymorphism(void);
		static void	testUnknownMateriaCreation(void);
		static void	testCharacterInventoryLimit(void);
		static void	testMateriaSourceLimit(void);
		static void	testInvalidUnequip(void);

		//Cahracters Tests:
		static void	testCharacterEquipUnequipBasic(void);
		static void	testCharacterUse(void);
		static void	testCharacterEdgeCases(void);
		static void	testCharacterDeepCopy(void);

		//Materia Duel Between Two Characters Tests:
		static void	testMateriaDuelBetweenTwoCharacters(void);
		static void	testMateriaSourceDinamic(void);
		static void	testMateriaSourceStack(void);

		//Orthodox Canonical Form Tests:
		static void	testOCF_MateriaSource(void);
		static void	testOCF_Character(void);
		static void	testOCF_MateriaTypes(void);
};

void	showMsg(const char* color, const char* msg, const char* reset);
void	showInstructionsTest(void);

#endif
