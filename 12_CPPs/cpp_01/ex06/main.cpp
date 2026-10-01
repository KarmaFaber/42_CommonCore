/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 13:39:41 by mzolotar          #+#    #+#             */
/*   Updated: 2025/09/01 12:19:04 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Harl.hpp"

int main (int argc, char **argv)
{
	Harl harl;
	if (argc != 2)
	{
		std::cout << CRED << "Usage: ./harlFilter <level>" << CRESET << std::endl;
		return (1);
	}
	harl.complain(argv[1]);
	
	return (0);
}
