/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 22:45:02 by mzolotar          #+#    #+#             */
/*   Updated: 2025/10/28 09:53:27 by mzolotar         ###   ########.fr       */
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
	showMsg(CMAGENTA, "Shows Cat making sound and accessing Brain ideas.", CRESET);
	showMsg(CMAGENTA, "-----------------------------", CRESET);

	Animal a("Animal");
	showMsg(CMAGENTA, "   ", CRESET);
	
	Cat c("Cat");
	showMsg(CMAGENTA, "   ", CRESET);

	std::cout << a.getType() << " says: ";
	a.makeSound();								//Animal method call -> Animal::makeSound()

	std::cout << c.getType() << " says: ";
	c.makeSound();								//Cat method call (direct overriding of Animal method makeSound()) -> Cat::makeSound()

	// Brain ideas
	showMsg(CBLACK, "Cat ideas: ", CRESET);
	for (int i = 0; i < 3; i++)
		std::cout << "     - " << c.getBrain()->getIdea(i) << std::endl;
	showMsg(CMAGENTA, "   ", CRESET);
}

void	Test::testPolymorphism()
{
	showMsg(CMAGENTA, "----------------------------------------", CRESET);
	showMsg(CMAGENTA, "--- 2_test TEST POLYMORPHISM RIGHT 1 ---", CRESET);
	showMsg(CMAGENTA, "----------------------------------------", CRESET);
	showMsg(CMAGENTA, "Polymorphism with Animal pointers to Dog and Cat.", CRESET);
	showMsg(CMAGENTA, "Shows makeSound() virtual calls and Brain ideas.", CRESET);
	showMsg(CMAGENTA, "----------------------------------------", CRESET);

	const Animal* dog = new Dog();
	showMsg(CMAGENTA, "   ", CRESET);
	
	const Animal* cat = new Cat();
	showMsg(CMAGENTA, "   ", CRESET);

	std::cout << dog->getType() << " says: ";
	dog->makeSound();							// Dog::makeSound

	std::cout << cat->getType() << " says: ";
	cat->makeSound();							// Cat::makeSound

	int idea_index = 3;
	std::cout << "\nCat idea" << " [" << idea_index << "]: " << std::endl;
	std::cout << static_cast<const Cat*>(cat)->getBrain()->getIdea(idea_index) << std::endl;

	std::cout << "\nDog idea" << " [" << idea_index << "]: " << std::endl;
	std::cout << static_cast<const Dog*>(dog)->getBrain()->getIdea(idea_index) << std::endl;
	
	showMsg(CMAGENTA, "   ", CRESET);
	delete dog;
	showMsg(CMAGENTA, "   ", CRESET);
	delete cat;
}

void	Test::testPolymorphismDog()
{
	showMsg(CMAGENTA, "----------------------------------------", CRESET);
	showMsg(CMAGENTA, " ---3_test TEST POLYMORPHISM RIGHT 2 ---", CRESET);
	showMsg(CMAGENTA, "----------------------------------------", CRESET);
	showMsg(CMAGENTA, "Dog object and pointer demonstrate polymorphic calls.", CRESET);
	showMsg(CMAGENTA, "Brain ideas are shown, modified, and displayed again.", CRESET);
	showMsg(CMAGENTA, "----------------------------------------", CRESET);
	
	Animal a;
	showMsg(CMAGENTA, "   ", CRESET);
	Dog d;
	showMsg(CMAGENTA, "   ", CRESET);

	std::cout << a.getType() << " says: ";
	a.makeSound();								//Animal method call -> Animal::makeSound()
	std::cout << d.getType() << " says: ";
	d.makeSound();								//Dog method call (direct overriding of Animal method makeSound()) -> Dog::makeSound()

	Animal* ptr = &d;
	ptr->makeSound();							// Diamic Polymorphism -> Dog::makeSound()

	showMsg(CMAGENTA, "\nInitial Dog ideas: ", CRESET);
	for (int i = 0; i < 5; i++)
		std::cout << "  - " << d.getBrain()->getIdea(i) << std::endl;
		
	showMsg(CMAGENTA, "\nChanging Dog ideas ...", CRESET);
	int idea_index = 3;
	d.getBrain()->setIdea(idea_index, "ff15");
	std::cout << "Dog new idea" << " ["<< idea_index << "]: "
			  << d.getBrain()->getIdea(idea_index) << std::endl;

	showMsg(CMAGENTA, "\nFinal Dog ideas: ", CRESET);
	for (int i = 0; i < 5; i++)
		std::cout << "  - " << d.getBrain()->getIdea(i) << std::endl;
	showMsg(CMAGENTA, "   ", CRESET);
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
	showMsg(CMAGENTA, "Shows static binding, Brain ideas can be modified manually.", CRESET);
	showMsg(CMAGENTA, "--------------------------------------------", CRESET);
	
	WrongAnimal a;
	showMsg(CMAGENTA, "   ", CRESET);
	WrongCat c;
	showMsg(CMAGENTA, "   ", CRESET);

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
	showMsg(CMAGENTA, "   ", CRESET);
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
	showMsg(CMAGENTA, "   ", CRESET);

	std::cout << w_cat->getType() << " says: ";
	w_cat->makeSound();							//static binding -> ! virtual == ! Polymorphism -> WrongAnimal::makeSound()

	static_cast<const WrongCat*>(w_cat)->getBrain()->setIdea(0, "Looking for food");

	//delete w_cat;								//not virtual destructor, therefore, just calls ~WrongAnimal(). WrogCat -> leaves resources unreleased or even causes segfaults

	showMsg(CMAGENTA, "   ", CRESET);
	delete static_cast < const WrongCat* > (w_cat);	//secure delete
}
