/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 10:17:00 by mzolotar          #+#    #+#             */
/*   Updated: 2025/09/24 08:28:13 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

int main(void)
{
	Zombie *horde;
	int zombie_num = 7;
	
	std::cout << CBLUE << "=== Creating horde ===" << CRESET << std::endl;
	horde = zombieHorde(zombie_num, "HordeMember");
	if (horde == NULL)
		return (1);
	for (int i = 0; i < zombie_num; ++i)
		horde[i].announce();
	delete [] horde; 

	std::cout << CBLUE << "\n=== Creating horde that should fail ===" << CRESET << std::endl;
	zombie_num = 0;
	Zombie *horde_fail;
	horde_fail = zombieHorde(zombie_num, "HordeMember");
	if (horde_fail == NULL)
		return (1);
	for (int i = 0; i < zombie_num; ++i)
		horde[i].announce();
	delete [] horde_fail; 
	
	return (0);
}
