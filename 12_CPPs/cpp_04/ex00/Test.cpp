/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 22:45:02 by mzolotar          #+#    #+#             */
/*   Updated: 2025/10/28 09:48:52 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Test.hpp"

void	showMsg(const char* color, const char* msg, const char* reset)
{
	std::cout << color << msg << reset << std::endl;
}

void	Test::testOverwrite()
{
	showMsg(CMAGENTA, "-----------------------------", CRESET);
	showMsg(CMAGENTA, "--- 1_test TEST OVERWRITE ---", CRESET);
	showMsg(CMAGENTA, "-----------------------------", CRESET);
	showMsg(CMAGENTA, "Demonstrates overriding of Animal methods by Cat.", CRESET);
	showMsg(CMAGENTA, "Shows Cat making sound.", CRESET);
	showMsg(CMAGENTA, "-----------------------------", CRESET);

	Animal a("Animal");
	showMsg(CMAGENTA, "   ", CRESET);
	
	Cat c("Cat");
	showMsg(CMAGENTA, "   ", CRESET);

	std::cout << a.getType() << " says: ";
	a.makeSound();								// Animal::makeSound

	std::cout << c.getType() << " says: ";
	c.makeSound();								// Cat::makeSound (overriding)
	showMsg(CMAGENTA, "   ", CRESET);
}

void	Test::testPolymorphism()
{
	showMsg(CMAGENTA, "--------------------------------", CRESET);
	showMsg(CMAGENTA, "--- 2_test TEST POLYMORPHISM ---", CRESET);
	showMsg(CMAGENTA, "--------------------------------", CRESET);
	showMsg(CMAGENTA, "Polymorphism with Animal pointers to Dog and Cat.", CRESET);
	showMsg(CMAGENTA, "Shows makeSound() virtual calls.", CRESET);
	showMsg(CMAGENTA, "--------------------------------", CRESET);

	const Animal* dog = new Dog();
	showMsg(CMAGENTA, "   ", CRESET);
	
	const Animal* cat = new Cat();
	showMsg(CMAGENTA, "   ", CRESET);

	std::cout << dog->getType() << " says: ";
	dog->makeSound();							// Dog::makeSound (dinamic polimorthism)

	std::cout << cat->getType() << " says: ";
	cat->makeSound();							// Cat::makeSound (dinamic polimorthism)
	showMsg(CMAGENTA, "   ", CRESET);

	delete dog;
	showMsg(CMAGENTA, "   ", CRESET);
	
	delete cat;
	showMsg(CMAGENTA, "   ", CRESET);
}

void	Test::testPolymorphismDog()
{
	showMsg(CMAGENTA, "------------------------------------", CRESET);
	showMsg(CMAGENTA, "--- 3_test TEST POLYMORPHISM DOG ---", CRESET);
	showMsg(CMAGENTA, "------------------------------------", CRESET);
	showMsg(CMAGENTA, "Demonstrates polymorphic call via Animal pointer.", CRESET);
	showMsg(CMAGENTA, "Shows Dog object calling makeSound through base ptr.", CRESET);
	showMsg(CMAGENTA, "------------------------------------", CRESET);
	
	Animal a;
	showMsg(CMAGENTA, "   ", CRESET);

	Dog d;
	showMsg(CMAGENTA, "   ", CRESET);

	std::cout << a.getType() << " says: ";
	a.makeSound();								//Animal method call
	std::cout << d.getType() << " says: ";
	d.makeSound();								//Dog method call (direct overriding of Animal method makeSound())

	Animal* ptr = &d;
	ptr->makeSound();							//Dinamic Polymorphism
	showMsg(CMAGENTA, "   ", CRESET);
}

void	Test::testOverwriteWrongAnimal()
{
	showMsg(CMAGENTA, "-----------------------------------------", CRESET);
	showMsg(CMAGENTA, "--- 4_test TEST OVERWRITE WRONGANIMAL ---", CRESET);
	showMsg(CMAGENTA, "-----------------------------------------", CRESET);
	showMsg(CMAGENTA, "WrongAnimal methods overridden by WrongCat object.", CRESET);
	showMsg(CMAGENTA, "Shows direct calls from object work.", CRESET);
	showMsg(CMAGENTA, "-----------------------------------------", CRESET);

	WrongAnimal a("WrongAnimal");
	showMsg(CMAGENTA, "   ", CRESET);
	
	WrongCat c("WrongCat");
	showMsg(CMAGENTA, "   ", CRESET);

	std::cout << a.getType() << " says: ";
	a.makeSound();								//WrongAnimal method call

	std::cout << c.getType() << " says: ";
	c.makeSound();								//WrongCat method call (direct overriding of WrongAnimal method makeSound())
	showMsg(CMAGENTA, "   ", CRESET);
}

void	Test::testPolymorphismWrongCat()
{
	showMsg(CMAGENTA, "--------------------------------------------", CRESET);
	showMsg(CMAGENTA, "--- 5_test TEST NO POLYMORPHISM WRONGCAT ---", CRESET);
	showMsg(CMAGENTA, "--------------------------------------------", CRESET);
	showMsg(CMAGENTA, "WrongAnimal pointer calls WrongCat method.", CRESET);
	showMsg(CMAGENTA, "Static binding prevents polymorphism.", CRESET);
	showMsg(CMAGENTA, "--------------------------------------------", CRESET);
	
	WrongAnimal a;
	showMsg(CMAGENTA, "   ", CRESET);
	
	WrongCat c;
	showMsg(CMAGENTA, "   ", CRESET);

	std::cout << a.getType() << " says: ";
	a.makeSound();									//WrongAnimal method call
	std::cout << c.getType() << " says: ";
	c.makeSound();									//WrongCat method call (direct overriding of WrongAnimal method makeSound())

	WrongAnimal* ptr = &c;
	std::cout << ptr->getType() << " says: ";
	ptr->makeSound();								//WrongCat::makeSound -> Dinamic Polymorphism
	showMsg(CMAGENTA, "   ", CRESET);
}

void	Test::testWrongPolymorphism()
{
	showMsg(CMAGENTA, "-------------------------------------------", CRESET);
	showMsg(CMAGENTA, "--- 6_test TEST WRONG & NO POLYMORPHISM ---", CRESET);
	showMsg(CMAGENTA, "-------------------------------------------", CRESET);
	showMsg(CMAGENTA, "Demonstrates segfault risk deleting WrongCat via base pointer.", CRESET);
	showMsg(CMAGENTA, "Static binding prevents polymorphic destruction.", CRESET);
	showMsg(CMAGENTA, "------------------------------------------", CRESET);

	const WrongAnimal* w_cat = new WrongCat();
	showMsg(CMAGENTA, "   ", CRESET);

	std::cout << w_cat->getType() << " says: ";
	w_cat->makeSound();							//static binding -> ! virtual == ! Polymorphism -> WrongAnimal::makeSound()

	//delete w_cat;								//not virtual destructor, therefore, just calls ~WrongAnimal(). WrogCat -> leaves resources unreleased or even causes segfaults
	
	showMsg(CMAGENTA, "   ", CRESET);
	delete static_cast < const WrongCat* > (w_cat);	//secure delete: ~WrongCat() + ~WrongAnimal()
}
