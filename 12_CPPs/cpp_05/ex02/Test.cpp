/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 10:55:40 by mzolotar          #+#    #+#             */
/*   Updated: 2025/11/14 11:49:04 by mzolotar         ###   ########.fr       */
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
			throw (InvalidInput());
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
		case 3:
			test_3();
			break;
		default:
			throw InvalidInput();
	}
	return (true);
}

void	Test::test_1(void)
{
	showMsg(BG_BRIGHT_YELLOW, "[T]Test 1: ShrubberyCreationForm class", CRESET);
	
	try
	{
		//AForm form(); // -> abstract class, we can't instanciate this object
		Bureaucrat b("Notaryx", 130);  // Grade 130 (can sign and exec)
		ShrubberyCreationForm s("garden");

		std::cout << CMAGENTA << b << CRESET << std::endl;
		std::cout << CMAGENTA << s << CRESET << std::endl;

		std::cout << CMAGENTA << "\n[T]--- Signing form ---" << CRESET << std::endl;
		b.signForm(s);  // (grade 130 <= 145)

		std::cout << CMAGENTA << "\n[T]--- Executing form ---" << CRESET << std::endl;
		b.executeForm(s);
	}
	catch (std::exception &e)
	{
		std::cout << CRED << "Exception: " << e.what() << CRESET << std::endl;
	}
}

void	Test::test_2(void)
{
	showMsg(BG_BRIGHT_YELLOW, "[T]Test 2: RobotomyRequestForm class", CRESET);
	showMsg(CMAGENTA, "   ", CRESET);
	try
	{
		Bureaucrat b("Clericon", 72);
		RobotomyRequestForm r("Oni");

		std::cout << CMAGENTA << b << CRESET << std::endl;
		std::cout << CMAGENTA << r << CRESET << std::endl;

		std::cout << CMAGENTA << "\n[T]--- Signing form ---" << CRESET << std::endl;
		b.signForm(r);  // (grade 40 <= 72)

		std::cout << CMAGENTA << "\n[T]--- Executing form ---" << CRESET << std::endl;
		b.executeForm(r);
	}
	catch (std::exception &e)
	{
		std::cout << CRED << e.what() << CRESET << std::endl;
	}
}

void	Test::test_3(void)
{

	showMsg(BG_BRIGHT_YELLOW, "[T]Test 3: PresidentialPardonForm class", CRESET);
	showMsg(CMAGENTA, "   ", CRESET);
	try
	{
		Bureaucrat b("Clericon", 2);
		PresidentialPardonForm r("Oni");

		std::cout << CMAGENTA << b << CRESET << std::endl;
		std::cout << CMAGENTA << r << CRESET << std::endl;

		std::cout << CMAGENTA << "\n[T]--- Signing form ---" << CRESET << std::endl;
		b.signForm(r);  // (grade 3 <= 25)

		std::cout << CMAGENTA << "\n[T]--- Executing form ---" << CRESET << std::endl;
		b.executeForm(r);
	}
	catch (std::exception &e)
	{
		std::cout << CRED << e.what() << CRESET << std::endl;
	}
}

/******************************************************************************/
/*                              EXCEPTIONS                                   */
/******************************************************************************/
const char* Test::InvalidInput::what() const throw()
{
	return ("[TEST_EXCEPTION] Incorrect input!");
}
