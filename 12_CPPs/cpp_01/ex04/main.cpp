/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 08:57:21 by mzolotar          #+#    #+#             */
/*   Updated: 2025/09/24 08:31:27 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ReplaceData.hpp"

int main(int argc, char** argv)
{
	if (argc != 4)
	{
		std::cout << CRED << "Error: wrong number of arguments. Use: <filename> <s1> <s2>"
				  << CRESET << std::endl;
		return (1);
	}
	ReplaceData example_1(argv[1], argv[2], argv[3]);
	if (!example_1.replaceFile())
		return (1);
	return (0);
}
