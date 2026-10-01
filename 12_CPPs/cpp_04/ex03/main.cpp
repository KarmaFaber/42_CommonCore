/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 12:57:07 by mzolotar          #+#    #+#             */
/*   Updated: 2025/10/28 10:02:51 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Colors.h"
#include "Test.hpp"
#include <cstring>

static int invalidInput()
{
	showMsg(RED, "Incorrect input! Choose one of the following options: ", RESET);
	showInstructionsTest();
	return (1);
}

int main(int argc, char** argv)
{
	if (argc != 2)
		return (invalidInput());
		
	if (strcmp(argv[1], "0") == 0)
		Test::testSubject();
	else if (strcmp(argv[1], "1") == 0)
		Test::instantiateAbstactcClass();
	else if (strcmp(argv[1], "2") == 0)
		Test::testPolymorphism();
	else if (strcmp(argv[1], "3") == 0)
		Test::testUnknownMateriaCreation();
	else if (strcmp(argv[1], "4") == 0)
		Test::testCharacterInventoryLimit();
	else if (strcmp(argv[1], "5") == 0)
		Test::testMateriaSourceLimit();
	else if (strcmp(argv[1], "6") == 0)
		Test::testInvalidUnequip();
	else if (strcmp(argv[1], "7") == 0)
		Test::testCharacterEquipUnequipBasic();
	else if (strcmp(argv[1], "8") == 0)
		Test::testCharacterUse();
	else if (strcmp(argv[1], "9") == 0)
		Test::testCharacterEdgeCases();
	else if (strcmp(argv[1], "10") == 0)
		Test::testCharacterDeepCopy();
	else if (strcmp(argv[1], "11") == 0)
		Test::testMateriaDuelBetweenTwoCharacters();
	else if (strcmp(argv[1], "12") == 0)
		Test::testMateriaSourceDinamic();
	else if (strcmp(argv[1], "13") == 0)
		Test::testMateriaSourceStack();
	else if (strcmp(argv[1], "14") == 0)
		Test::testOCF_MateriaSource();
	else if (strcmp(argv[1], "15") == 0)
		Test::testOCF_Character();
	else if (strcmp(argv[1], "16") == 0)
		Test::testOCF_MateriaTypes();
	else
		return (invalidInput());
	return (0);
}
