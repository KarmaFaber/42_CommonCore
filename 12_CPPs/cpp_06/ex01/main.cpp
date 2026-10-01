/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 11:24:02 by mzolotar          #+#    #+#             */
/*   Updated: 2025/11/06 12:10:13 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Serializer.hpp"

#define CRED				"\033[0;31m"
#define CGREEN				"\033[0;32m"
#define CMAGENTA			"\033[0;35m"
#define CCYAN				"\e[36m"
#define CRESET				"\033[0m"

int main()
{
	Data	data;
	data._name = "Amelia";
	data._age = 42;
	data._score = 99.9;

	std::cout << CMAGENTA << "Original Data:\n";
	std::cout << "  Name:  " << data._name << "\n";
	std::cout << "  Age:   " << data._age << "\n";
	std::cout << "  Score: " << data._score << "\n\n" << CRESET << std::endl;

	std::cout << "Original ptr:           " << &data << std::endl;

	// --- SERIALIZACIÓN ---
	uintptr_t raw = Serializer::serialize(&data);
	std::cout << "Serialized (uintptr_t): " << raw << std::endl;

	// --- DESERIALIZACIÓN ---
	Data* ptr = Serializer::deserialize(raw);
	std::cout << "Deserialized ptr:       " << ptr << std::endl;

	std::cout << CCYAN << "\nData read from deserialized pointer:\n";
	std::cout << "  Name:  " << ptr->_name << "\n";
	std::cout << "  Age:   " << ptr->_age << "\n";
	std::cout << "  Score: " << ptr->_score << "\n\n" << CRESET << std::endl;

	if (ptr == &data)
		std::cout << CGREEN << "Pointers match! (Same memory address)\n" << CRESET << std::endl;
	else
		std::cout << CRED << "Pointers do not match.\n" << CRESET << std::endl;

	return 0;
}
