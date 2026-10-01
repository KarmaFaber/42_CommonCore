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

#include "ClapTrap.hpp"

static void	showMsg (const char *color, const char *msg, const char *reset)
{
	std::cout << color << msg << reset << std::endl;
}

static void printStats(ClapTrap& obj)
{
	std::cout << CMAGENTA
			  << "---- ClapTrap Stats ----"
			  << "\nClapTrap name: " << obj.getName()
			  << "\nHit Points: " << obj.getHitPoints()
			  << "\nEnergy Points: " << obj.getEnergyPoints()
			  << "\nAttack Damage: " << obj.getAttackDamage()
			  << CRESET
			  << std::endl;
}

static void	test_1( void )
{
	showMsg (CBLUE, "\n--- Test 1: Copy Constructor ---", CRESET);
	ClapTrap original("Original");
	printStats(original);

	original.setHitPoints(77);
	original.setEnergyPoints(88);
	original.setAttackDamage(33);

	ClapTrap copy = original;
	printStats(copy);
}

static void	test_2( void )
{
	showMsg (CBLUE, "\n--- Test 2: Copy Assignment Operator ---", CRESET);
	ClapTrap original("Original");
	printStats(original);

	original.setHitPoints(77);
	original.setEnergyPoints(88);
	original.setAttackDamage(33);
	
	ClapTrap assigned("Assigned");
	assigned = original;
	printStats(assigned);
}

static void	test_3( void )
{
	ClapTrap c1("Ana");
	ClapTrap c2("Gabriel");

	std::cout << "\n--- Basic attack test ---\n";
	c1.attack(c2.getName());
	c2.attack(c1.getName());

	std::cout << "\n--- Damage test ---\n";
	c1.takeDamage(3);
	c2.takeDamage(12);

	std::cout << "\n--- Repair test ---\n";
	c1.beRepaired(5);
	c2.beRepaired(5);

	std::cout << "\n--- Energy test ---\n";
	while (c1.getEnergyPoints() > 0)
		c1.attack(c2.getName());

	printStats(c1);
	printStats(c2);
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
