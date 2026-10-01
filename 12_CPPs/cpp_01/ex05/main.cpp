/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 13:39:41 by mzolotar          #+#    #+#             */
/*   Updated: 2025/09/01 11:56:44 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Harl.hpp"

int main(void)
{
	Harl harl;
		
	std::cout << CBLUE << "=== Testing Harl's complaints ===" << CRESET << std::endl;
	std::cout << std::endl;
	std::cout << CGREEN  << "Testing DEBUG level:" << CRESET << std::endl;
	harl.complain("DEBUG");
	std::cout << std::endl;
	
	std::cout << CGREEN  << "Testing INFO level:" << CRESET << std::endl;
	harl.complain("INFO");
	std::cout << std::endl;
	
	std::cout << CGREEN  << "Testing WARNING level:" << CRESET << std::endl;
	harl.complain("WARNING");
	std::cout << std::endl;
	
	std::cout << CGREEN  << "Testing ERROR level:" << CRESET << std::endl;
	harl.complain("ERROR");
	std::cout << std::endl;
	
	std::cout << CGREEN  << "Testing invalid level:" << CRESET << std::endl;
	harl.complain("INVALID");
	std::cout << std::endl;

	std::cout << CGREEN  << "Testing empty level:" << CRESET << std::endl;
	harl.complain("");
	std::cout << std::endl;
	
	std::cout << CGREEN  << "Testing lowercase level:" << CRESET << std::endl;
	harl.complain("debug");
	std::cout << std::endl;
	std::cout << CBLUE << "=== Harl is done complaining ===" << CRESET << std::endl;
	
	return (0);
}
