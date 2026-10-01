/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 11:30:30 by mzolotar          #+#    #+#             */
/*   Updated: 2025/11/10 12:42:02 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "MutantStack.hpp"
#include <list>

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
#define TEST_2				"   ⇢   Test 2: own test -> <int>   ⇠   "
#define TEST_3				"   ⇢   Test 3: own test -> <string>   ⇠   "
#define TEST_B				"\n⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒\n"
#define TEST_BB				"\n⭒⭒⭒⭒⭒⭒\n"
#define TEST_E				"\n========================== END OF TESTS. ==========================="

static void	showMsg(const char* color, const char* msg, const char* reset)
{
	std::cout << color << msg << reset << std::endl;
}

void test_1_subject()
{
	showMsg(BG_BRIGHT_YELLOW, TEST_1 ,CRESET);
	MutantStack<int> mstack;
	mstack.push(5);
	mstack.push(17);
	std::cout << mstack.top() << std::endl;
	mstack.pop();
	std::cout << mstack.size() << std::endl;
	mstack.push(3);
	mstack.push(5);
	mstack.push(737);
	//[...]
	mstack.push(0);
	MutantStack<int>::iterator it = mstack.begin();
	MutantStack<int>::iterator ite = mstack.end();
	++it;
	--it;
	while (it != ite)
	{
		std::cout << *it << std::endl;
		++it;
	}
	std::stack<int> s(mstack);
	showMsg(CBLACK, TEST_B ,CRESET);
}

//https://en.cppreference.com/w/cpp/container/list.html
void test_2_own_test()
{
	showMsg(BG_BRIGHT_YELLOW, TEST_2 ,CRESET);

	MutantStack<int> mstack;
	mstack.push(1);
	mstack.push(22);
	mstack.push(333);

	std::list<int> lst;
	lst.push_back(1);
	lst.push_back(22);
	lst.push_back(333);

	// ---- Iterador normal ----
	showMsg(CCYAN, "Iterator forward:" ,CRESET);
	{
		showMsg(CBLACK, "MutantStack: " ,CRESET);
		MutantStack<int>::iterator it = mstack.begin();
		for (; it != mstack.end(); ++it)
			std::cout << *it << " ";
		std::cout << std::endl;

		showMsg(CBLACK, "\nlist: " ,CRESET);
		std::list<int>::iterator lit = lst.begin();
		for (; lit != lst.end(); ++lit)
			std::cout << *lit << " ";
		std::cout << std::endl;
		showMsg(CBLACK, TEST_BB ,CRESET);
	}

	// ---- Const iterator ----
	showMsg(CCYAN, "Const iterator forward:" ,CRESET);
	{
		showMsg(CBLACK, "MutantStack: " ,CRESET);
		const MutantStack<int> cmstack = mstack;
		MutantStack<int>::const_iterator it = cmstack.begin();
		for (; it != cmstack.end(); ++it)
			std::cout << *it << " ";
		std::cout << std::endl;
		showMsg(CBLACK, TEST_BB ,CRESET);
	}

	// ---- Reverse iterator ----
	showMsg(CCYAN, "Reverse iterator:" ,CRESET);
	{
		showMsg(CBLACK, "MutantStack: " ,CRESET);
		MutantStack<int>::reverse_iterator rit = mstack.rbegin();
		for (; rit != mstack.rend(); ++rit)
			std::cout << *rit << " ";
		std::cout << std::endl;

		showMsg(CBLACK, "\nlist: " ,CRESET);
		std::list<int>::reverse_iterator rlit = lst.rbegin();
		for (; rlit != lst.rend(); ++rlit)
			std::cout << *rlit << " ";
		std::cout << std::endl;
		showMsg(CBLACK, TEST_BB ,CRESET);
	}

	// ---- Const reverse iterator ----
	showMsg(CCYAN, "Const reverse iterator:" ,CRESET);
	{
		showMsg(CBLACK, "MutantStack: " ,CRESET);
		const MutantStack<int> cmstack = mstack;
		MutantStack<int>::const_reverse_iterator rit = cmstack.rbegin();
		for (; rit != cmstack.rend(); ++rit)
			std::cout << *rit << " ";
		std::cout << std::endl;
	}
	showMsg(CBLACK, TEST_B ,CRESET);
}

void test_3_string()
{
	showMsg(BG_BRIGHT_YELLOW, TEST_3 ,CRESET);

	// MutantStack de strings
	MutantStack<std::string> mstack;
	mstack.push("hello");
	mstack.push("World");
	mstack.push("42");

	// List de strings
	std::list<std::string> lst;
	lst.push_back("hola");
	lst.push_back("mundo");
	lst.push_back("42");

	// ---- Iterator forward ----
	showMsg(CCYAN, "Iterator forward:" ,CRESET);
	showMsg(CBLACK, "MutantStack: ", CRESET);
	for (MutantStack<std::string>::iterator it = mstack.begin(); it != mstack.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl;

	showMsg(CBLACK, "list: ", CRESET);
	for (std::list<std::string>::iterator it = lst.begin(); it != lst.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl;
	showMsg(CBLACK, TEST_BB ,CRESET);

	// ---- Reverse iterator ----
	showMsg(CCYAN, "Reverse iterator:" ,CRESET);
	showMsg(CBLACK, "MutantStack: ", CRESET);
	for (MutantStack<std::string>::reverse_iterator rit = mstack.rbegin(); rit != mstack.rend(); ++rit)
		std::cout << *rit << " ";
	std::cout << std::endl;

	showMsg(CBLACK, "list: ", CRESET);
	for (std::list<std::string>::reverse_iterator rit = lst.rbegin(); rit != lst.rend(); ++rit)
		std::cout << *rit << " ";
	std::cout << std::endl;
	showMsg(CBLACK, TEST_BB ,CRESET);

	// ---- Const iterator ----
	showMsg(CCYAN, "Const iterator forward:" ,CRESET);
	const MutantStack<std::string> cmstack = mstack;
	for (MutantStack<std::string>::const_iterator it = cmstack.begin(); it != cmstack.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl;
	showMsg(CBLACK, TEST_BB ,CRESET);

	// ---- Const reverse iterator ----
	showMsg(CCYAN, "Const reverse iterator:" ,CRESET);
	for (MutantStack<std::string>::const_reverse_iterator rit = cmstack.rbegin(); rit != cmstack.rend(); ++rit)
		std::cout << *rit << " ";
	std::cout << std::endl;

	showMsg(CBLACK, TEST_BB ,CRESET);
}

int main()
{
	showMsg(CMAGENTA, TEST_S ,CRESET);
	test_1_subject();
	test_2_own_test();
	test_3_string();
	showMsg(CMAGENTA, TEST_E ,CRESET);
	return (0);
}
