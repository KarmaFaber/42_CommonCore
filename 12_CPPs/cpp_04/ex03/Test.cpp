/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 22:45:02 by mzolotar          #+#    #+#             */
/*   Updated: 2025/10/28 09:43:19 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Test.hpp"

void	showMsg(const char* color, const char* msg, const char* reset)
{
	std::cout << color << msg << reset << std::endl;
}

void	showInstructionsTest(void)
{
	showMsg(BLACK, "Subject Test: ", RESET);
	showMsg(BLACK, "    ./interface <0>  ➙ TEST 0: Subject default test code.", RESET);
	showMsg(BLACK, "General Errors: ", RESET);
	showMsg(BLACK, "    ./interface <1>  ➙ TEST 1: Attempting to instantiate abstract classes (theoretical only).", RESET);
	showMsg(BLACK, "    ./interface <2>  ➙ TEST 2: Polymorphism with Base Pointers.", RESET);
	showMsg(BLACK, "    ./interface <3>  ➙ TEST 3: Create Unknown Materia. ", RESET);
	showMsg(BLACK, "    ./interface <4>  ➙ TEST 4: Character Inventory Limit.", RESET);
	showMsg(BLACK, "    ./interface <5>  ➙ TEST 5: MateriaSource Limit.", RESET);
	showMsg(BLACK, "    ./interface <6>  ➙ TEST 6: Unequip Invalid Index.", RESET);
	showMsg(BLACK, "Cahracters Tests:  ", RESET);
	showMsg(BLACK, "    ./interface <7>  ➙ TEST 7: Basic Character equip/unequip.", RESET);
	showMsg(BLACK, "    ./interface <8>  ➙ TEST 8: Character use() behavior.", RESET);
	showMsg(BLACK, "    ./interface <9>  ➙ TEST 9: Character edge cases & errors.", RESET);
	showMsg(BLACK, "    ./interface <10> ➙ TEST 10: Deep copy & independence.", RESET);
	showMsg(BLACK, "Materia Duel Between Two Characters Tests:  ", RESET);
	showMsg(BLACK, "    ./interface <11> ➙ TEST 11: Materia Duel Between Two Characters.", RESET);
	showMsg(BLACK, "    ./interface <12> ➙ TEST 12: MateriaSource Full Behavior → dynamic interface (IMateriaSource*).", RESET);
	showMsg(BLACK, "    ./interface <13> ➙ TEST 13: MateriaSource Stack Behavior → direct instance (MateriaSource src).", RESET);
	showMsg(BLACK, "Orthodox Canonical Form Tests:  ", RESET);
	showMsg(BLACK, "    ./interface <14> ➙ TEST 13: Orthodox Canonical Form - MateriaSource.", RESET);
	showMsg(BLACK, "    ./interface <15> ➙ TEST 14: Orthodox Canonical Form - Character.", RESET);
	showMsg(BLACK, "    ./interface <16> ➙ TEST 15: Orthodox Canonical Form - AMateria / Ice / Cure.\n", RESET);
}

//Subject Test:
//=======================./interface <0>=========================================
void	Test::testSubject()
{
	showMsg(BG_BRIGHT_CYAN, "[TEST 0] Subject default test code.", RESET);
	
	IMateriaSource* src = new MateriaSource();
	
	src->learnMateria(new Ice());
	src->learnMateria(new Cure());
	
	ICharacter* me = new Character("me");
	AMateria* tmp;
	tmp = src->createMateria("ice");
	me->equip(tmp);
	tmp = src->createMateria("cure");
	me->equip(tmp);
	ICharacter* bob = new Character("bob");
	me->use(0, *bob);
	me->use(1, *bob);
	
	delete bob;
	delete me;
	delete src;
}

//General Errors
//=======================./interface <1>=========================================
void	Test::instantiateAbstactcClass(void)
{
	showMsg(BG_BRIGHT_CYAN, "[TEST 1] Attempting to instantiate abstract classes (theoretical only)", RESET);

	//IMateriaSource imateria;		//object of abstract class type "..." is not allowed:
	//AMateria amateria;			//object of abstract class type "..." is not allowed:
	//ICharacter icharacter;		//object of abstract class type "..." is not allowed:

	showMsg(BLACK, "   ", RESET);
	showMsg(BLACK, "[T] If you have not uncommented these lines, it means that the code has been successfully compiled and executed.", RESET);
	showMsg(BLACK, "[T] Try uncommenting some of the lines in this test and see what happens.", RESET);
	showMsg(BLACK, "   ", RESET);
}

//=======================./interface <2>=========================================
void	Test::testPolymorphism(void)
{
	showMsg(BG_BRIGHT_CYAN, "[TEST 2] Polymorphism with Base Pointers", RESET);

	AMateria* ice = new Ice();
	showMsg(BLACK, "   ", RESET);
	
	AMateria* cure = new Cure();
	showMsg(BLACK, "   ", RESET);
	
	ICharacter* bob = new Character("Bob");
	showMsg(BLACK, "   ", RESET);

	showMsg(BLACK, "[T] Calling use() from AMateria* pointer (dynamic dispatch):", RESET);
	ice->use(*bob);
	cure->use(*bob);
	showMsg(BLACK, "   ", RESET);

	delete ice;
	showMsg(BLACK, "   ", RESET);
	delete cure;
	showMsg(BLACK, "   ", RESET);
	delete bob;
}

//=======================./interface <3>=========================================
void	Test::testUnknownMateriaCreation(void)
{
	showMsg(BG_BRIGHT_CYAN, "[TEST 3] Create Unknown Materia.", RESET);

	IMateriaSource* src = new MateriaSource();
	showMsg(BLACK, "   ", RESET);

	Ice* ice = new Ice();
	showMsg(BLACK, "   ", RESET);
	
	Cure* cure = new Cure();
	
	showMsg(BLACK, "\n[T] Calling learnMateria(ice):", RESET);
	src->learnMateria(ice);
	showMsg(BLACK, "   ", RESET);
	src->learnMateria(new Ice());

	showMsg(BLACK, "\n[T] Calling learnMateria(cure):", RESET);
	src->learnMateria(cure);
	showMsg(BLACK, "   ", RESET);

	showMsg(BLACK, "[T]Calling createMateria(unknown materia):", RESET);
	AMateria* tmp = src->createMateria("fire");
	if (!tmp)
		showMsg(BLACK, "[T] ✔️  Unknown type handled correctly (returned NULL)\n", RESET);
	else
	{
		showMsg(RED, "[T] ❌  ERROR: Expected NULL for unknown type\n", RESET);
		delete tmp;
	}
	delete src;
	showMsg(BLACK, "   ", RESET);
}

//=======================./interface <4>=========================================
void	Test::testCharacterInventoryLimit(void)
{
	showMsg(BG_BRIGHT_CYAN, "[TEST 4] Character Inventory Limit.", RESET);

	ICharacter* hero = new Character("Hero");
	showMsg(BLACK, "   ", RESET);

	AMateria* m1 = new Ice();
	showMsg(BLACK, "   ", RESET);

	AMateria* m2 = new Ice();
	showMsg(BLACK, "   ", RESET);

	AMateria* m3 = new Ice();
	showMsg(BLACK, "   ", RESET);
	
	AMateria* m4 = new Ice();
	showMsg(BLACK, "   ", RESET);
	
	AMateria* m5 = new Ice();

	showMsg(BLACK, "\n[T] Calling equip(n):", RESET);
	hero->equip(m1);
	hero->equip(m2);
	hero->equip(m3);
	hero->equip(m4);
	hero->equip(m5);

	showMsg(BLACK, "   ", RESET);
	delete hero;
}

//=======================./interface <5>=========================================
void	Test::testMateriaSourceLimit(void)
{
	showMsg(BG_BRIGHT_CYAN, "[TEST 5] MateriaSource Limit.", RESET);

	MateriaSource* src = new MateriaSource();

	showMsg(BLACK, "\n[T] Calling learnMateria(cure or ice):", RESET);
	src->learnMateria(new Ice());
	showMsg(BLACK, "   ", RESET);
	
	AMateria* ice1 = new Ice();
	src->learnMateria(ice1);
	showMsg(BLACK, "   ", RESET);

	AMateria* cure1 = new Cure();
	src->learnMateria(cure1);
	showMsg(BLACK, "   ", RESET);

	AMateria* ice2 = new Ice();
	src->learnMateria(ice2);
	showMsg(BLACK, "   ", RESET);

	AMateria* cure2 = new Cure();
	src->learnMateria(cure2);
	showMsg(BLACK, "   ", RESET);

	AMateria* ice3 = new Ice();
	src->learnMateria(ice3);
	showMsg(BLACK, "   ", RESET);

	delete src;
}

//=======================./interface <6>=========================================
void	Test::testInvalidUnequip(void)
{
	showMsg(BG_BRIGHT_CYAN, "[TEST 6] Unequip Invalid Index.", RESET);

	ICharacter* hero = new Character("Hero");
	AMateria* ice = new Ice();
	
	showMsg(BLACK, "\n[T] Calling equip(ice):", RESET);
	hero->equip(ice);

	showMsg(BLACK, "\n[T] Calling unequip(-1):", RESET);
	hero->unequip(-1);

	showMsg(BLACK, "\n[T] Calling unequip(5):", RESET);
	hero->unequip(5);

	showMsg(BLACK, "\n[T] Calling unequip(0):", RESET);
	hero->unequip(0);
	showMsg(BLACK, "   ", RESET);

	delete hero;
}

//Cahracters Tests:
//=======================./interface <7>=========================================
void Test::testCharacterEquipUnequipBasic(void)
{
	showMsg(BG_BRIGHT_CYAN, "[TEST 7] Character Equip / Unequip Basic", RESET);

	MateriaSource src;
	showMsg(BLACK, "   ", RESET);
	
	AMateria* ice = new Ice();
	AMateria* cure = new Cure();
	
	showMsg(BLACK, "\n[T] Calling learnMateria(ice)", RESET);
	src.learnMateria(ice);

	showMsg(BLACK, "\n[T] Calling learnMateria(cure)", RESET);
	src.learnMateria(cure);

	showMsg(BLACK, "   ", RESET);
	Character alice("Alice");

	showMsg(BLACK, "\n[T] Calling equip(ice):", RESET);
	alice.equip(src.createMateria("ice"));

	showMsg(BLACK, "\n[T] Calling equip(cure):", RESET);
	alice.equip(src.createMateria("cure"));
	
	showMsg(BLACK, "\n[T] Calling unequip(1) ➙ ✔️ valid range", RESET);
	alice.unequip(1);

	showMsg(BLACK, "\n[T] Calling unequip(42) ➙ ❌ out of range:", RESET);
	alice.unequip(42);

	showMsg(BLACK, "   ", RESET);
}

//=======================./interface <8>=========================================
void Test::testCharacterUse(void)
{
	showMsg(BG_BRIGHT_CYAN, "[TEST 8] Character use() Behavior", RESET);

	MateriaSource src;
	showMsg(BLACK, "   ", RESET);
	
	AMateria* ice = new Ice();
	AMateria* cure = new Cure();

	showMsg(BLACK, "\n[T] Calling learnMateria(ice)", RESET);
	src.learnMateria(ice);

	showMsg(BLACK, "\n[T] Calling learnMateria(cure)", RESET);
	src.learnMateria(cure);

	showMsg(BLACK, "   ", RESET);
	Character alice("Alice");
	Character bob("Bob");

	showMsg(BLACK, "\n[T] Calling equip(ice):", RESET);
	alice.equip(src.createMateria("ice"));

	showMsg(BLACK, "\n[T] Calling equip(cure):", RESET);
	alice.equip(src.createMateria("cure"));

	showMsg(BLACK, "\n[T] Calling use equipped materia ➙  ✔️  valid materia", RESET);
	alice.use(0, bob);

	showMsg(BLACK, "\n[T] Calling use equipped materia ➙  ✔️  valid materia", RESET);
	alice.use(1, bob);

	showMsg(BLACK, "\n[T] Calling use equipped materia ➙  ❌  void materia", RESET);
	alice.use(3, bob);

	showMsg(BLACK, "   ", RESET);
}

//=======================./interface <9>=========================================
void Test::testCharacterEdgeCases(void)
{
	showMsg(BG_BRIGHT_CYAN, "[TEST 9] Character Error Handling & Edge Cases", RESET);

	MateriaSource src;
	showMsg(BLACK, "   ", RESET);
	
	AMateria* ice = new Ice();
	showMsg(BLACK, "\n[T] Calling learnMateria(ice)", RESET);
	src.learnMateria(ice);
	showMsg(BLACK, "   ", RESET);

	Character alice("Alice");

	showMsg(BLACK, "\n[T] Calling equip(NULL) ➙  ❌  NULL Materia", RESET);
	alice.equip(NULL);

	showMsg(BLACK, "\n[T] Fill out complete inventory:", RESET);
	for (int i = 0; i < 4; i++)
		alice.equip(src.createMateria("ice"));

	showMsg(BLACK, "\n[T] Trying to equip when it is full", RESET);
	alice.equip(src.createMateria("ice"));

	showMsg(BLACK, "\n[T] Calling unequip(-1) ➙  ❌  invalid range", RESET);
	alice.unequip(-1);
	showMsg(BLACK, "\n[T] Calling unequip(99) ➙  ❌  invalid range", RESET);
	alice.unequip(99);

	showMsg(BLACK, "\n[T] Calling unequip(2) ➙  ✔️  valid range", RESET);
	alice.unequip(2);

	showMsg(BLACK, "   ", RESET);
}

//=======================./interface <10>=========================================
void Test::testCharacterDeepCopy(void)
{
	showMsg(BG_BRIGHT_CYAN, "[TEST 10] Character Deep Copy Validation", RESET);

	MateriaSource src;
	showMsg(BLACK, "   ", RESET);
	
	AMateria* ice = new Ice();
	AMateria* cure = new Cure();
	
	showMsg(BLACK, "\n[T] Calling learnMateria(ice)", RESET);
	src.learnMateria(ice);

	showMsg(BLACK, "\n[T] Calling learnMateria(cure)", RESET);
	src.learnMateria(cure);

	Character alice("Alice");
	showMsg(BLACK, "   ", RESET);
	
	showMsg(BLACK, "\n[T] Calling equip(ice):", RESET);
	alice.equip(src.createMateria("ice"));

	showMsg(BLACK, "\n[T] Calling equip(cure):", RESET);
	alice.equip(src.createMateria("cure"));

	showMsg(BLACK, "\n[T] Calling Copy Constructor:", RESET);
	Character copy(alice);
	
	showMsg(BLACK, "\n[T] Using materia from copy", RESET);
	copy.use(0, alice);

	showMsg(BLACK, "\n[T] Using materia from copy", RESET);
	copy.use(1, alice);
	showMsg(BLACK, "   ", RESET);
}


//Materia Duel Between Two Characters Tests:
//=======================./interface <11>=========================================
void	Test::testMateriaDuelBetweenTwoCharacters(void)
{
	showMsg(BG_BRIGHT_CYAN, "[TEST 11] Materia Duel Between Two Characters", RESET);

	MateriaSource src;
	showMsg(BLACK, "   ", RESET);

	AMateria* ice = new Ice();
	AMateria* cure = new Cure();
	showMsg(BLACK, "   ", RESET);

	showMsg(BLACK, "[T] Learning Ice and Cure:", RESET);
	src.learnMateria(ice);
	src.learnMateria(cure);
	showMsg(BLACK, "   ", RESET);

	Character alice("Alice");
	Character bob("Bob");

	showMsg(BLACK, "\n[T] Equipping Alice (offense):", RESET);
	alice.equip(src.createMateria("ice"));
	alice.equip(src.createMateria("ice"));

	showMsg(BLACK, "\n[T] Equipping Bob (support):", RESET);
	bob.equip(src.createMateria("cure"));
	bob.equip(src.createMateria("cure"));

	showMsg(BLACK, "\n ⚔️  Duel Start!", RESET);

	showMsg(BLACK, "   [T]Alice attacks Bob with ice:", RESET);
	alice.use(0, bob);
	alice.use(1, bob);

	showMsg(BLACK, "   [T]Bob heals himself and Alice:", RESET);
	bob.use(0, bob);
	bob.use(1, alice);

	showMsg(BLACK, "\n   [T] Using invalid slots:", RESET);
	alice.use(4, bob);
	bob.use(-1, alice);
	showMsg(BLACK, "   ", RESET);
}

//=======================./interface <12>=========================================
void	Test::testMateriaSourceDinamic(void)
{
	showMsg(BG_BRIGHT_CYAN,
			"[TEST 12] MateriaSource Full Behavior → dynamic interface (IMateriaSource*)",
			RESET);

	IMateriaSource* src = new MateriaSource();

	showMsg(BLACK, "\n[T] Learning Materias:", RESET);
	for (int i = 0; i < 3; i++)
	{
		src->learnMateria(new Ice());
		showMsg(BLACK, "   ", RESET);
		src->learnMateria(new Cure());
		showMsg(BLACK, "   ", RESET);
	}

	showMsg(BLACK, "[T] Creating known Materias:", RESET);
	AMateria* m1 = src->createMateria("ice");
	AMateria* m2 = src->createMateria("cure");
	if (m1 && m2)
		showMsg(BLACK, "[T] ✔️  Known Materias successfully created.\n", RESET);
	else
		showMsg(RED, "[T] ❌  ERROR: Failed to create known Materias!\n", RESET);


	showMsg(BLACK, "[T] Creating unknown Materia 'fire':", RESET);
	AMateria* unknown = src->createMateria("fire");
	if (!unknown)
		showMsg(BLACK,"[T] ✔️  Unknown Materia correctly returned NULL.\n", RESET);
	else
	{
		showMsg(RED, "[T] ❌  ERROR: Unknown Materia should return NULL!\n", RESET);
		delete unknown;
	}
		
	delete m1;
	delete m2;
	showMsg(BLACK, "   ", RESET);

	delete src;
	showMsg(BLACK, "   ", RESET);
}

//=======================./interface <13>=========================================
void	Test::testMateriaSourceStack(void)
{
	showMsg(BG_BRIGHT_CYAN,
			"[TEST 13] MateriaSource Stack Behavior → direct instance (MateriaSource src;)",
			RESET);

	MateriaSource src;
	showMsg(BLACK, "   ", RESET);

	showMsg(BLACK, "\n[T] Learning Materias:", RESET);
	for (int i = 0; i < 3; i++)
	{
		src.learnMateria(new Ice());
		showMsg(BLACK, "   ", RESET);
		src.learnMateria(new Cure());
		showMsg(BLACK, "   ", RESET);
	}

	showMsg(BLACK, "[T] Creating Materias:", RESET);
	AMateria* m1 = src.createMateria("ice");
	showMsg(BLACK, "   ", RESET);
	AMateria* m2 = src.createMateria("cure");
	showMsg(BLACK, "   ", RESET);
	AMateria* unknown = src.createMateria("fire");

	if (!unknown)
		showMsg(BLACK, "[T] ✔️  Unknown Materia returned NULL.\n", RESET);

	delete m1;
	delete m2;
	showMsg(BLACK, "   ", RESET);
}

//Orthodox Canonical Form Tests:
//=======================./interface <14>=========================================
void Test::testOCF_MateriaSource(void)
{
	showMsg(BG_BRIGHT_CYAN, "[TEST 13] Orthodox Canonical Form - MateriaSource", RESET);

	MateriaSource original;
	showMsg(BLACK, "   ", RESET);

	AMateria* ice = new Ice();
	AMateria* cure = new Cure();

	showMsg(BLACK, "\n[T] Calling learnMateria(ice)", RESET);
	original.learnMateria(ice);

	showMsg(BLACK, "\n[T] Calling learnMateria(cure)", RESET);
	original.learnMateria(cure);

	showMsg(BLACK, "\n[T] Creating copy via copy constructor", RESET);
	MateriaSource copyCtor(original);

	showMsg(BLACK, "\n[T] Creating another copy via assignment operator", RESET);
	MateriaSource assigned;
	assigned = original;

	showMsg(BLACK, "   ", RESET);
}

//=======================./interface <15>=========================================
void Test::testOCF_Character(void)
{
	showMsg(BG_BRIGHT_CYAN, "[TEST 14] Orthodox Canonical Form - Character", RESET);

	MateriaSource src;
	showMsg(BLACK, "   ", RESET);
	
	AMateria* ice = new Ice();
	AMateria* cure = new Cure();
	showMsg(BLACK, "   ", RESET);

	showMsg(BLACK, "[T] Calling learnMateria(ice)", RESET);
	src.learnMateria(ice);
	showMsg(BLACK, "\n[T] Calling learnMateria(cure)", RESET);
	src.learnMateria(cure);
	showMsg(BLACK, "   ", RESET);

	Character original("Alice");
	showMsg(BLACK, "\n[T] Calling equip(ice):", RESET);
	original.equip(src.createMateria("ice"));

	showMsg(BLACK, "\n[T] Calling equip(cure):", RESET);
	original.equip(src.createMateria("cure"));

	showMsg(BLACK, "\n[T] Creating Character copy via copy constructor", RESET);
	Character copyCtor(original);

	showMsg(BLACK, "\n[T] Creating another Character via assignment operator", RESET);
	Character assigned("Temp");
	assigned = original;

	showMsg(BLACK, "\n[T] Using Materia from copies to verify independence", RESET);
	copyCtor.use(0, original);
	assigned.use(1, original);
	showMsg(BLACK, "   ", RESET);
}

//=======================./interface <16>=========================================
void Test::testOCF_MateriaTypes(void)
{
	showMsg(BG_BRIGHT_CYAN, "[TEST 15] Orthodox Canonical Form - AMateria / Ice / Cure", RESET);

	Ice* iceOriginal = new Ice();
	showMsg(BLACK, "   ", RESET);
	Cure* cureOriginal = new Cure();

	showMsg(BLACK, "\n[T] Copy constructors:", RESET);
	Ice iceCopy(*iceOriginal);
	Cure cureCopy(*cureOriginal);

	showMsg(BLACK, "\n[T] Assignment operators:", RESET);
	Ice iceAssigned;
	Cure cureAssigned;

	iceAssigned = *iceOriginal;
	cureAssigned = *cureOriginal;
	showMsg(BLACK, "   ", RESET);

	delete iceOriginal;
	delete cureOriginal;
	showMsg(BLACK, "   ", RESET);
}
