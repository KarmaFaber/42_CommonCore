/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zombieHorde.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 10:18:49 by mzolotar          #+#    #+#             */
/*   Updated: 2025/09/24 08:19:47 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

Zombie* zombieHorde( int N, std::string name )
{
	if (N <= 0)
	{
		std::cout << CRED << "Error: N must be greater than 0." << CRESET << std::endl;
		return (NULL);
	}

	Zombie *horde = new Zombie[N];
	if (horde == NULL)
	{
		std::cout << CRED << "Allocation of the horde failed." << CRESET << std::endl;
		return (NULL);
	}
	for (int i = 0; i < N; i++)
		horde[i].setName(name);
	return (horde);
}
