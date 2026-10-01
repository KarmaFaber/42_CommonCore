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

#include "ScavTrap.hpp"

static void	showMsg (const char *color, const char *msg, const char *reset)
{
	std::cout << color << msg << reset << std::endl;
}

static void printStats(ScavTrap& obj)
{
	std::cout << CMAGENTA
			  << "---- ScavTrap Stats ----"
			  << "\nScavTrap name: " << obj.getName()
			  << "\nHit Points: " << obj.getHitPoints()
			  << "\nEnergy Points: " << obj.getEnergyPoints()
			  << "\nAttack Damage: " << obj.getAttackDamage()
			  << CRESET
			  << std::endl;
}

static void	test_1( void )
{
	showMsg (CMAGENTA, "\n--- Test 1: Copy Constructor ---", CRESET);
	ScavTrap original("Original");
	printStats(original);

	original.setHitPoints(15);
	original.setEnergyPoints(20);
	original.setAttackDamage(5);
	ScavTrap copy = original;

	printStats(copy);
}

static void	test_2( void )
{
	showMsg (CMAGENTA, "\n--- Test 2: Copy Assignment Operator ---", CRESET);
	ScavTrap original("Original");
	printStats(original);

	original.setHitPoints(15);
	original.setEnergyPoints(20);
	original.setAttackDamage(5);
	ScavTrap assigned("Assigned");
	assigned = original;

	printStats(assigned);
}

static void	test_3( void )
{
	ScavTrap enemy("Enemy");
	ScavTrap guardian("Guardian");

	showMsg (CMAGENTA, "\n--- Initial status ---\n", CRESET);
	printStats(enemy);
	printStats(guardian);

	std::cout << "\n--- Basic attack test ---\n";
	std::cout << "\n----- Inherit Methods -----\n";
	enemy.attack(guardian.getName());
	guardian.attack(enemy.getName());
	std::cout << "\n----- Own Methods -----\n";
	guardian.guardGate();

	showMsg (CMAGENTA, "\n--- Final status ---\n", CRESET);
	printStats(enemy);
	printStats(guardian);

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
