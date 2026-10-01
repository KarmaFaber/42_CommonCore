/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 22:45:02 by mzolotar          #+#    #+#             */
/*   Updated: 2025/10/28 09:56:24 by mzolotar         ###   ########.fr       */
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
	showMsg(CMAGENTA, "AAnimal -> abstract calss, cannot be instantiated ", CRESET);
	showMsg(CMAGENTA, "Shows Cat making sound and accessing Brain ideas.", CRESET);
	showMsg(CMAGENTA, "-----------------------------", CRESET);

	showMsg(CBLACK, "   ", CRESET);
	showMsg(CBLACK, "[T] Try to uncomment the line that creates the AAnimal object!", CRESET);
	//AAnimal a("Animal");
	showMsg(CBLACK, "   ", CRESET);
	Cat c("Cat");

	//std::cout << a.getType() << " says: ";
	//a.makeSound();								//Animal method call

	showMsg(CBLACK, "   ", CRESET);
	std::cout << c.getType() << " says: ";
	c.makeSound();									//Cat method call (direct overriding of Animal method makeSound())
	showMsg(CBLACK, "   ", CRESET);

	showMsg(CBLACK, "Cat ideas: ", CRESET);
	for (int i = 0; i < 3; i++)
		std::cout << "     - " << c.getBrain()->getIdea(i) << std::endl;
	showMsg(CBLACK, "   ", CRESET);
}

void	Test::testPolymorphism()
{
	showMsg(CMAGENTA, "----------------------------------------", CRESET);
	showMsg(CMAGENTA, "--- 2_test TEST POLYMORPHISM RIGHT 1 ---", CRESET);
	showMsg(CMAGENTA, "----------------------------------------", CRESET);
	showMsg(CMAGENTA, "Polymorphism with AAnimal pointers to Dog and Cat.", CRESET);
	showMsg(CMAGENTA, "Shows makeSound() virtual calls and Brain ideas.", CRESET);
	showMsg(CMAGENTA, "----------------------------------------", CRESET);

	const AAnimal* dog = new Dog();
	showMsg(CBLACK, "   ", CRESET);
	const AAnimal* cat = new Cat();
	showMsg(CBLACK, "   ", CRESET);

	std::cout << dog->getType() << " says: ";
	dog->makeSound();							// Dog::makeSound

	std::cout << cat->getType() << " says: ";
	cat->makeSound();							// Cat::makeSound

	int idea_index = 3;
	std::cout << "\nCat idea" << " [" << idea_index << "]: " << std::endl;
	std::cout << static_cast<const Cat*>(cat)->getBrain()->getIdea(idea_index) << std::endl;

	std::cout << "\nDog idea" << " [" << idea_index << "]: " << std::endl;
	std::cout << static_cast<const Dog*>(dog)->getBrain()->getIdea(idea_index) << std::endl;
	
	showMsg(CBLACK, "   ", CRESET);
	delete dog;
	showMsg(CBLACK, "   ", CRESET);
	delete cat;
}

void	Test::testPolymorphismDog()
{
	showMsg(CMAGENTA, "----------------------------------------", CRESET);
	showMsg(CMAGENTA, " ---3_test TEST POLYMORPHISM RIGHT 2 ---", CRESET);
	showMsg(CMAGENTA, "----------------------------------------", CRESET);
	showMsg(CMAGENTA, "AAnimal -> abstract calss, cannot be instantiated ", CRESET);
	showMsg(CMAGENTA, "Dog object and pointer demonstrate polymorphic calls.", CRESET);
	showMsg(CMAGENTA, "Brain ideas are shown, modified, and displayed again.", CRESET);
	showMsg(CMAGENTA, "----------------------------------------", CRESET);
	
	showMsg(CBLACK, "\n[T] Try to uncomment the line that creates the AAnimal object!\n", CRESET);
	//AAnimal a;
	Dog d;
	showMsg(CBLACK, "   ", CRESET);

	//std::cout << a.getType() << " says: ";
	//a.makeSound();								//Animal method call
	std::cout << d.getType() << " says: ";
	d.makeSound();									//Dog method call (direct overriding of Animal method makeSound())

	AAnimal* ptr = &d;
	ptr->makeSound();								//Polymorphism

	showMsg(CMAGENTA, "\nInitial Dog ideas: ", CRESET);
	for (int i = 1; i < 3; i++)
		std::cout << "  - " << d.getBrain()->getIdea(i) << std::endl;
	
	showMsg(CMAGENTA, "\nChanging Dog ideas [Test 1]", CRESET);
	int idea_index = 1;
	d.getBrain()->setIdea(1, "ff15");
	std::cout << "Dog new idea" << " ["<< idea_index << "]: "
			  << d.getBrain()->getIdea(idea_index) << std::endl;
	
	showMsg(CMAGENTA, "\nChanging Dog ideas [Test 2]", CRESET);
	idea_index = 0;
	d.getBrain()->setIdea(idea_index, "ff15");
	std::cout << "Dog new idea" << " ["<< idea_index << "]: "
			  << d.getBrain()->getIdea(idea_index) << std::endl;

	showMsg(CMAGENTA, "\nFinal Dog ideas: ", CRESET);
	for (int i = 0; i < 3; i++)
		std::cout << "  - " << d.getBrain()->getIdea(i) << std::endl;
	showMsg(CBLACK, "   ", CRESET);
}

void	Test::testOverwriteWrongAnimal()
{
	showMsg(CMAGENTA, "-----------------------------------------", CRESET);
	showMsg(CMAGENTA, " ---4_test TEST OVERWRITE WRONGANIMAL ---", CRESET);
	showMsg(CMAGENTA, "-----------------------------------------", CRESET);
	showMsg(CMAGENTA, "WrongAnimal methods are overridden by WrongCat.", CRESET);
	showMsg(CMAGENTA, "Shows that calls from object work, but no polymorphism.", CRESET);
	showMsg(CMAGENTA, "-----------------------------------------", CRESET);
	
	WrongAnimal a("WrongAnima");
	showMsg(CBLACK, "   ", CRESET);
	WrongCat c("WrongCat");
	showMsg(CBLACK, "   ", CRESET);

	std::cout << a.getType() << " says: ";
	a.makeSound();								//WrongAnimal method call

	std::cout << c.getType() << " says: ";
	c.makeSound();								//WrongCat method call (direct overriding of WrongAnimal method makeSound())
	showMsg(CBLACK, "   ", CRESET);
}

void	Test::testPolymorphismWrongCat()
{
	showMsg(CMAGENTA, "--------------------------------------------", CRESET);
	showMsg(CMAGENTA, "--- 5_test TEST NO POLYMORPHISM WRONGCAT ---", CRESET);
	showMsg(CMAGENTA, "--------------------------------------------", CRESET);
	showMsg(CMAGENTA, "WrongAnimal pointer calls WrongCat method.", CRESET);
	showMsg(CMAGENTA, "Shows static binding, Brain ideas can be modified manually.", CRESET);
	showMsg(CMAGENTA, "--------------------------------------------", CRESET);
	
	WrongAnimal a;
	showMsg(CBLACK, "   ", CRESET);
	WrongCat c;
	showMsg(CBLACK, "   ", CRESET);

	std::cout << a.getType() << " says: ";
	a.makeSound();									//WrongAnimal method call
	std::cout << c.getType() << " says: ";
	c.makeSound();									//WrongCat method call (direct overriding of WrongAnimal method makeSound())

	c.getBrain()->setIdea(0, "Sleeping in the sink");
	c.getBrain()->setIdea(1, "Chasing shadows");

	WrongAnimal* ptr = &c;
	std::cout << ptr->getType() << " says: ";
	ptr->makeSound();								//static binding -> ! virtual == ! Polymorphism -> WrongAnimal::makeSound

	std::cout << "\nWrongCat ideas via c: " << std::endl;
	for (int i = 0; i < 2; i++)
		std::cout << "  - " << c.getBrain()->getIdea(i) << std::endl;
	showMsg(CBLACK, "   ", CRESET);
}

void	Test::testWrongPolymorphism()
{
	showMsg(CMAGENTA, "------------------------------------------", CRESET);
	showMsg(CMAGENTA, "---6_test TEST WRONG & NO POLYMORPHISM ---", CRESET);
	showMsg(CMAGENTA, "------------------------------------------", CRESET);
	showMsg(CMAGENTA, "Shows segfault risk if WrongCat deleted via WrongAnimal pointer.", CRESET);
	showMsg(CMAGENTA, "Demonstrates accessing Brain safely and correct deletion.", CRESET);
	showMsg(CMAGENTA, "------------------------------------------", CRESET);

	const WrongAnimal* w_cat = new WrongCat();
	showMsg(CBLACK, "   ", CRESET);

	std::cout << w_cat->getType() << " says: ";
	w_cat->makeSound();								//static binding -> ! virtual == ! Polymorphism -> WrongAnimal::makeSound()

	static_cast<const WrongCat*>(w_cat)->getBrain()->setIdea(0, "Looking for food");

	//delete w_cat;									//not virtual destructor, therefore, just calls ~WrongAnimal(). WrogCat -> leaves resources unreleased or even causes segfaults

	showMsg(CBLACK, "   ", CRESET);
	delete static_cast < const WrongCat* > (w_cat);	//secure delete
}

void	Test::testBrainErrorHandling()
{
	showMsg(CMAGENTA, "----------------------------------------", CRESET);
	showMsg(CMAGENTA, "--- 7_test TEST BRAIN ERROR HANDLING ---", CRESET);
	showMsg(CMAGENTA, "----------------------------------------", CRESET);
	showMsg(CMAGENTA, "Demonstrates out_of_range exception when", CRESET);
	showMsg(CMAGENTA, "accessing Brain ideas with invalid index.", CRESET);
	showMsg(CMAGENTA, "Safe error handling with try/catch shown.", CRESET);
	showMsg(CMAGENTA, "----------------------------------------", CRESET);

	Dog d;
	showMsg(CBLACK, "   ", CRESET);

	showMsg(CMAGENTA, "\n---Valid access--------------------------------", CRESET);
	try
	{
		std::cout << "Dog idea[0]: " << d.getBrain()->getIdea(0) << std::endl;
	}
	catch (const std::out_of_range& e)
	{
		std::cerr << CRED << "Exception: " << e.what() << CRESET << std::endl;
	}

	showMsg(CMAGENTA, "\n---Invalid access (negative index)--------------", CRESET);
	try
	{
		std::cout << "Dog idea[-1]: " << d.getBrain()->getIdea(-1) << std::endl;
	}
	catch (const std::out_of_range& e)
	{
		std::cerr << CRED << "Exception: " << e.what() << CRESET << std::endl;
	}

	showMsg(CMAGENTA, "\n---Invalid access (out of upper bound)----------", CRESET);
	try
	{
		d.getBrain()->setIdea(150, "Too far!");
	}
	catch (const std::out_of_range& e)
	{
		std::cerr << CRED << "Exception: " << e.what() << CRESET << std::endl;
	}
	showMsg(CBLACK, "   ", CRESET);
}
