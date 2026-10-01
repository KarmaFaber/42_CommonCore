/* ************************************************************************** */
/*	                                                                        */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 08:06:05 by mzolotar          #+#    #+#             */
/*   Updated: 2025/09/03 09:50:10 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "DiamondTrap.hpp"

static void	showMsg (const char *color, const char *msg, const char *reset)
{
	std::cout << color << msg << reset << std::endl;
}

static void printStats(DiamondTrap& obj)
{
	std::cout << CMAGENTA
			  << "---- DiamondTrap Stats ----"
			  << "\nDiamondTrap name: " << obj.getDiamondName()
			  << "\nClapTrap name: " << obj.ClapTrap::getName()
			  << "\nName: " << obj.getName()
			  << "\nHit Points: " << obj.getHitPoints()
			  << "\nEnergy Points: " << obj.getEnergyPoints()
			  << "\nAttack Damage: " << obj.getAttackDamage()
			  << CRESET
			  << std::endl;
}

static void	test_1( void )
{
	showMsg (CMAGENTA, "\n--- Test 1: Copy Constructor ---", CRESET);
	DiamondTrap original("Original");
	DiamondTrap copy = original;

	showMsg (CMAGENTA, "\n--- Final status Copy---", CRESET);
	printStats(original);
	showMsg (CMAGENTA, "\n", CRESET);
	printStats(copy);
	std::cout << "\n----- Own Methods -----\n";
	original.whoAmI();
	copy.whoAmI();

	showMsg (CMAGENTA, "\n", CRESET);
}

static void	test_2( void )
{
	showMsg (CMAGENTA, "\n--- Test 2: Copy Assignment Operator ---", CRESET);
	DiamondTrap original("Original");
	DiamondTrap assigned("Assigned");
	assigned = original;

	showMsg (CMAGENTA, "\n--- Final status Asigned ---", CRESET);
	printStats(original);
	printStats(assigned);
	std::cout << "\n----- Own Methods -----\n";
	original.whoAmI();
	assigned.whoAmI();

	showMsg (CMAGENTA, "\n", CRESET);
}

static void	test_3( void )
{
	DiamondTrap enemy("Enemy");
	DiamondTrap monster("Monster");

	showMsg (CMAGENTA, "\n--- Initial status ---", CRESET);
	printStats(enemy);
	showMsg (CMAGENTA, "\n", CRESET);
	printStats(monster);

	std::cout << "\n--- Basic attack test ---";
	std::cout << "\n----- Inherit Methods -----\n";
	enemy.attack(monster.getName());
	monster.attack(enemy.getName());
	std::cout << "\n----- Own Methods -----\n";
	monster.whoAmI();
	enemy.whoAmI();

	showMsg (CMAGENTA, "\n--- Final status ---", CRESET);
	printStats(enemy);
	showMsg (CMAGENTA, "\n", CRESET);
	printStats(monster);
	showMsg (CMAGENTA, "\n", CRESET);

}

int main(int argc, char** argv) 
{
	if (argc != 2)
	{
		showMsg (CRED, "incorrect input!", CRESET);
		return 1;
	}
	if (strcmp(argv[1], "1") == 0)
		test_1();
	else if (strcmp(argv[1], "2") == 0)
		test_2();
	else if (strcmp(argv[1], "3") == 0)
		test_3();
	else
		showMsg (CRED, "incorrect input!", CRESET);
	return 0;
}
