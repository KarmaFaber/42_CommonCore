/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 09:32:50 by mzolotar          #+#    #+#             */
/*   Updated: 2025/08/28 10:47:54 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

int main(void)
{
	std::cout << CBLUE << "=== Creating zombie on heap ===" << CRESET << std::endl;
	Zombie *zombie_heap = newZombie("HeapZombie");
	zombie_heap->announce();

	std::cout << CBLUE << "=== Creating zombie on stack ===" << CRESET << std::endl;
	randomChump("StackZombie");

	std::cout << CBLUE << "=== Deleting heap zombie ===" << CRESET << std::endl;
	delete zombie_heap;

	return (0);
}