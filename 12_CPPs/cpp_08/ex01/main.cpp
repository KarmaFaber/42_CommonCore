/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 11:07:55 by mzolotar          #+#    #+#             */
/*   Updated: 2025/11/10 11:29:02 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Span.hpp"
#include <iostream>
#include <cstdlib>

#define CMAGENTA			"\033[0;35m"
#define CRED				"\033[0;31m"
#define CGREEN				"\033[0;32m"
#define CCYAN				"\e[36m"
#define CBLACK				"\033[0;30m"
#define CYELLOW				"\033[0;33m"
#define BG_BRIGHT_YELLOW	"\e[103m"
#define CRESET				"\033[0m"
#define TEST_S				"========================== START TESTS: ============================"
#define TEST_1				"   ⇢   Test 1: subject code   ⇠   "
#define TEST_2				"   ⇢   Test 2: big nums test   ⇠   "
#define TEST_B				"⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒"
#define TEST_E				"\n========================== END OF TESTS. ==========================="

static void	showMsg(const char* color, const char* msg, const char* reset)
{
	std::cout << color << msg << reset << std::endl;
}

int main()
{
	showMsg(CMAGENTA, TEST_S ,CRESET);
	try
	{
		showMsg(BG_BRIGHT_YELLOW, TEST_1 ,CRESET);
		Span sp(5);

		sp.addNumber(6);
		sp.addNumber(3);
		sp.addNumber(17);
		sp.addNumber(9);
		sp.addNumber(11);
		//sp.addNumber(77); //	Try uncommenting this line of code and see what happens.
		
		std::cout << "Shortest span: " << sp.shortestSpan() << std::endl;
		std::cout << "Longest span: " << sp.longestSpan() << std::endl;

		std::cout << std::endl << TEST_B << std::endl << std::endl;
		
		showMsg(BG_BRIGHT_YELLOW, TEST_2 ,CRESET);
		Span big(100000);
		std::vector<int> tmp;
		for (int i = 0; i < 100000; ++i)
			tmp.push_back(i);
		big.addNumber(tmp.begin(), tmp.end());
		std::cout << "Big shortest: " << big.shortestSpan() << std::endl;
		std::cout << "Big longest: " << big.longestSpan() << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << "Caught exception: "
			<< CRED << e.what() 
			<< CRESET << std::endl;
	}
	showMsg(CMAGENTA, TEST_E ,CRESET);
}
