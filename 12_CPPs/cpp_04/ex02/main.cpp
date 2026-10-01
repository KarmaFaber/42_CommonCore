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

#include "Test.hpp"

//1_test ➙ Test::testOverwrite() ➙ direct overriding of methods inherited from class Animal + virtual
//2_test ➙ Test::testPolymorphism() ➙ dinamic polymorphism
//3_test ➙ Test::testPolymorphismDog() ➙ dinamic polymorphism
//4_test ➙ Test::testOverwriteWrongAnimal() ➙ direct overriding of methods inherited from class WrongAnimal ! virtual
//5_test ➙ Test::testPolymorphismWrongCat() ➙ static binding -> ! virtual == ! Polymorphism -> WrongAnimal::makeSound
//6_test ➙ Test::testWrongPolymorphism() ➙ static binding -> ! virtual == ! Polymorphism -> WrongAnimal::makeSound()
//7_test ➙ Test::testBrainErrorHandling()➙ error handling with try/catch && out_of_range

int main(int argc, char** argv) 
{
	if (argc != 2)
	{
		showMsg (CRED, "incorrect input!", CRESET);
		return (1);
	}
	if (strcmp(argv[1], "1") == 0)
		Test::testOverwrite();
	else if (strcmp(argv[1], "2") == 0)
		Test::testPolymorphism();
	else if (strcmp(argv[1], "3") == 0)
		Test::testPolymorphismDog();
	else if (strcmp(argv[1], "4") == 0)
		Test::testOverwriteWrongAnimal();
	else if (strcmp(argv[1], "5") == 0)
		Test::testPolymorphismWrongCat();
	else if (strcmp(argv[1], "6") == 0)
		Test::testWrongPolymorphism();
	else if (strcmp(argv[1], "7") == 0)
		Test::testBrainErrorHandling();
	else
		showMsg (CRED, "incorrect input!", CRESET);
	return (0);
}
