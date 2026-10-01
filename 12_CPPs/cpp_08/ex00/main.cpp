/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 13:21:13 by mzolotar          #+#    #+#             */
/*   Updated: 2025/11/10 10:32:32 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "easyfind.hpp"
#include <vector>
#include <list>
#include <deque>
#include <iostream>

#define CMAGENTA			"\033[0;35m"
#define CRED				"\033[0;31m"
#define CGREEN				"\033[0;32m"
#define CCYAN				"\e[36m"
#define CBLACK				"\033[0;30m"
#define CYELLOW				"\033[0;33m"
#define BG_BRIGHT_YELLOW	"\e[103m"
#define CRESET				"\033[0m"
#define TEST_S				"========================== START TESTS: ============================"
#define TEST_1				"   ⇢   Test 1: std::vector<int>   ⇠   "
#define TEST_2				"   ⇢   Test 2: std::list<int>   ⇠   "
#define TEST_3				"   ⇢   Test 3: std::deque<int>   ⇠   "
#define TEST_B				"\n⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒\n"
#define TEST_E				"\n========================== END OF TESTS. ==========================="

static void	showMsg(const char* color, const char* msg, const char* reset)
{
	std::cout << color << msg << reset << std::endl;
}

void test_1_vestor()
{
		showMsg(BG_BRIGHT_YELLOW, TEST_1 ,CRESET);
		std::vector<int> v;
		for (int i = 0; i < 5; ++i)
			v.push_back(i);
		v.insert(v.begin(), 77);
		
		std::cout << "Vector: ";
		for (std::vector<int>::iterator it = v.begin(); it != v.end(); ++it)
			std::cout << *it << " ";
		
		try
		{
			int value = 3;
			std::cout << "\nSearch_1: " << value << std::endl;
			std::vector<int>::iterator it = easyfind(v, value);
			std::cout << " ✒  Found value: " << *it << std::endl;
		}
		catch (std::exception &e)
		{
			std::cout << " ✒  Caught exception: "
					  << CRED << e.what() 
					  << CRESET << std::endl;
		}

		try
		{
			int value_2 = 42;
			std::cout << "Search_2: " << value_2 << std::endl;
			easyfind(v, value_2);
		}
		catch (std::exception &e)
		{
			std::cout << " ✒  Caught exception: "
					  << CRED << e.what() 
					  << CRESET << std::endl;
		}
		showMsg(CBLACK, TEST_B ,CRESET);
}

void test_2_list()
{
	showMsg(BG_BRIGHT_YELLOW, TEST_2 ,CRESET);
	std::list<int> lst;
	for (int i = 10; i < 15; ++i)
		lst.push_back(i);

	std::cout << "List: ";
	for (std::list<int>::iterator it = lst.begin(); it != lst.end(); ++it)
		std::cout << *it << " ";

	try
	{
		int value = 12;
		std::cout << "\nSearch_1: " << value << std::endl;
		std::list<int>::iterator it = easyfind(lst, value);
		std::cout << " ✒  Found value: " << *it << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << " ✒  Caught exception: "
					<< CRED << e.what() 
					<< CRESET << std::endl;
	}

	try
	{
		int value_2 = 99;
		std::cout << "Search_2: " << value_2 << std::endl;
		easyfind(lst, value_2);
	}
	catch (std::exception &e)
	{
		std::cout << " ✒  Caught exception: "
					<< CRED << e.what() 
					<< CRESET << std::endl;
	}
	showMsg(CBLACK, TEST_B ,CRESET);
}
void test_3_deque()
{
	showMsg(BG_BRIGHT_YELLOW, TEST_3 ,CRESET);
	std::deque<int> dq;
	dq.push_back(7);
	dq.push_back(8);
	dq.push_back(9);

	std::cout << "\nDeque: ";
	for (std::deque<int>::iterator it = dq.begin(); it != dq.end(); ++it)
	{
		std::cout << *it << " ";
	}
	
	try
	{
		int value = 8;
		std::cout << "\nSearch_1: " << value << std::endl;
		std::deque<int>::iterator it = easyfind(dq, value);
		std::cout << " ✒  Found value: " << *it << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << " ✒  Caught exception: "
					<< CRED << e.what() 
					<< CRESET << std::endl;
	}

	try
	{
		int value_2 = 100;
		std::cout << "Search_2: " << value_2 << std::endl;
		easyfind(dq, value_2);
	}
	catch (std::exception &e)
	{
		std::cout << " ✒  Caught exception: "
					<< CRED << e.what() 
					<< CRESET << std::endl;
	}
}

int main()
{
	showMsg(CMAGENTA, TEST_S ,CRESET);
	test_1_vestor();
	test_2_list();
	test_3_deque();
	showMsg(CMAGENTA, TEST_E ,CRESET);
	return (0);
}
