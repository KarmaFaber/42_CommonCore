/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 08:15:12 by mzolotar          #+#    #+#             */
/*   Updated: 2026/02/05 13:38:58 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

int	main(int argc, char** argv)
{
	if (argc != 2)
	{
		showError (CRED, "Error", CRESET);
		return (1);
	}
	
	try
	{
		RPN calculator(argv[1]);
		std::cout << calculator.getResult() << std::endl;
	}
	catch (std::exception &e)
	{
		showError (CRED, e.what(), CRESET);
		return (1);
	}
	return (0);
}
