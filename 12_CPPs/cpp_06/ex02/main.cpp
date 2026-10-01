/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 12:14:26 by mzolotar          #+#    #+#             */
/*   Updated: 2025/11/06 12:33:58 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Base.hpp"
#include <iostream>

int main()
{
	Base* ptr = generate();   // genera un objeto aleatorio (A, B o C)
	std::cout << "\n--- identify(Base*) ---\n";
	identify(ptr);

	std::cout << "\n--- identify(Base&) ---\n";
	identify(*ptr);

	delete ptr;
	return (0);
}
