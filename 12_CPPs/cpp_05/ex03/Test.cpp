/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 10:55:40 by mzolotar          #+#    #+#             */
/*   Updated: 2025/11/14 11:51:43 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Test.hpp"

/******************************************************************************/
/*                            GLOBAL FUNCTIONS                                */
/******************************************************************************/
void	showMsg(const char* color, const char* msg, const char* reset)
{
	std::cout << color << msg << reset << std::endl;
}

void	testUse(void)
{
	showMsg(CBLACK, "[T]Use: ./program_name <n>", CRESET);
}

/******************************************************************************/
/*                            CLASS METHODS                                   */
/******************************************************************************/
bool	Test::findTest(char** argv)
{
	for (int i = 0; argv[1][i]; ++i)
	{
		if (!std::isdigit(argv[1][i]))
			throw InvalidInput();
	}
	int test_num = std::atoi(argv[1]);
	
	switch (test_num)
	{
		case 1:
			test_1();
			break;
		case 2:
			test_2();
			break;
		default:
			throw InvalidInput();
	}
	return (true);
}

void	Test::test_1(void)
{
	showMsg(BG_BRIGHT_YELLOW, "[T]Test 1: Intern class", CRESET);
	
	try
	{
		Intern Jr_Intern;
		AForm *robo_intern;

		std::cout << CMAGENTA << "\n[T]--- Incorrect form ---" << CRESET << std::endl;
		robo_intern = Jr_Intern.makeForm("DoYouKnowMe", "Hmmmm");
		
		std::cout << CMAGENTA << "\n[T]--- Correct form ---" << CRESET << std::endl;
		robo_intern = Jr_Intern.makeForm("RobotomyRequestForm", "World");
		if (robo_intern)
		{
			//std::cout << "Created form: " << robo_intern->getName() << std::endl;
			delete robo_intern;
		}
	}
	catch (std::exception &e)
	{
		std::cout << CRED << "Exception: " << e.what() << CRESET << std::endl;
	}
}

void	Test::test_2(void)
{
	showMsg(BG_BRIGHT_YELLOW, "[T]Test 2: ", CRESET);
	

	Intern Jr_Intern;
	AForm *robo_intern;

	std::cout << CMAGENTA << "\n[T]--- Incorrect form ---" << CRESET << std::endl;
	robo_intern = Jr_Intern.makeForm("DoYouKnowMe", "Hmmmm");
	
	std::cout << CMAGENTA << "\n[T]--- Correct form ---" << CRESET << std::endl;
	robo_intern = Jr_Intern.makeForm("RobotomyRequestForm", "World");
	if (robo_intern)
	{
		//std::cout << "Created form: " << robo_intern->getName() << std::endl;
		delete robo_intern;
	}
}

/******************************************************************************/
/*                              EXCEPTIONS                                   */
/******************************************************************************/
const char* Test::InvalidInput::what() const throw()
{
	return ("[TEST_EXCEPTION] Incorrect input!");
}
