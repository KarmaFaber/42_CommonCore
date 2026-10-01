/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Base.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 12:15:59 by mzolotar          #+#    #+#             */
/*   Updated: 2025/11/06 12:36:13 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"

Base::~Base() {}

Base* generate(void)
{
	std::srand(std::time(NULL));
	int r = std::rand() % 3;

	switch (r)
	{
		case 0:
			std::cout << "Generated A" << std::endl;
			return (new A);
		case 1:
			std::cout << "Generated B" << std::endl;
			return (new B);
		default:
			std::cout << "Generated C" << std::endl;
			return (new C);
	}
}

//dynamic_cast() -> Safely converts pointers and references to classes up, down, and sideways along the inheritance hierarchy.
void identify(Base* p)
{
	if (dynamic_cast<A*>(p))
		std::cout << "Type: A" << std::endl;
	else if (dynamic_cast<B*>(p))
		std::cout << "Type: B" << std::endl;
	else if (dynamic_cast<C*>(p))
		std::cout << "Type: C" << std::endl;
	else
		std::cout << "Unknown type" << std::endl;
}


void identify(Base& p)
{
	try
	{
		(void)dynamic_cast<A&>(p);
		std::cout << "Type: A" << std::endl;
		return;
	}
	catch (std::bad_cast&) {}

	try
	{
		(void)dynamic_cast<B&>(p);
		std::cout << "Type: B" << std::endl;
		return;
	}
	catch (std::bad_cast&) {}

	try
	{
		(void)dynamic_cast<C&>(p);
		std::cout << "Type: C" << std::endl;
		return;
	}
	catch (std::bad_cast&) {}

	std::cout << "Unknown type" << std::endl;
}
