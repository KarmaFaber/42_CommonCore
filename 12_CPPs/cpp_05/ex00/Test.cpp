/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 10:55:40 by mzolotar          #+#    #+#             */
/*   Updated: 2025/11/14 11:02:26 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Test.hpp"

/******************************************************************************/
/*						CONSTRUCTORS & DESTRUCTORS							  */
/******************************************************************************/
/*	Atribute Constructor	*/
Test::Test(int argc, char **argv)
{
	if (argc != 5)
		throw InvalidArgc();
	
	if (!validateArgv(argv))
			throw (InvalidInput());

	_test_num = std::atoi(argv[1]);
	_testName = argv[2];
	_testGrade = std::atoi(argv[3]);
	_test_index = std::atoi(argv[4]);
	_i = TETS_INDEX_DEFAULT;
	std::cout << "[C_TEST]Test Constructor." << std::endl;
}

/*	Desctructor				*/
Test::~Test()
{
	std::cout << "[D_TEST]Test Destructor." << std::endl;
}

/******************************************************************************/
/*							PRIVATE METHODS									  */
/******************************************************************************/
bool	Test::validateTestNum(char **argv)
{
	for (int i = 0; argv[1][i]; ++i)
	{
		if (!std::isdigit(argv[1][i]))
			return (false);
	}
	int valid_var = std::atoi(argv[1]);
	return (valid_var >= TETS_NUM_MIN && valid_var <= TETS_NUM_MAX);
}

bool	Test::validateName(char **argv)
{
	for (int i = 0; argv[2][i]; ++i)
	{
		if (!std::isalpha(argv[2][i]))
			return (false);
	}
	return (true);
}

bool Test::validateGrade(char **argv)
{
	int i = 0;
	if (argv[3][0] == '-')
		i = 1;
	for (; argv[3][i]; ++i)
	{
		if (!std::isdigit(argv[3][i]))
			return (false);
	}
	return (true);
}

bool	Test::validateTestIndex(char **argv)
{
	for (int i = 0; argv[4][i]; ++i)
	{
		if (!std::isdigit(argv[4][i]))
			return (false);
	}
	int valid_var = std::atoi(argv[4]);
	return (valid_var >= TETS_INDEX_MIN && valid_var <= TETS_INDEX_MAX);
}

bool	Test::validateArgv(char **argv)
{
	if (!validateTestNum(argv))
		throw InvalidTest();
	if (!validateName(argv))
		return (false);
	//if (!validateGrade(argv))
	//	return (false);
	if (!validateTestIndex(argv))
		return (false);	
	return (true);
}

/******************************************************************************/
/*							PUBLIC METHODS									  */
/******************************************************************************/
void	Test::runTest(void)
{
	switch (_test_num)
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
		case 4:
			test_4();
			break;
		default:
			throw (InvalidTest());
	}
}

/******************************************************************************/
/*								TESTS										  */
/******************************************************************************/
void	Test::test_1(void)
{
	std::cout << BG_BRIGHT_CYAN << "[T]Test 1: Unhandled exception (crash test 🚨 )"
			  << CRESET << " -> grade = " << _testGrade << ", steps = "
			  << _test_index << "." << std::endl;
	
	Bureaucrat b(_testName, _testGrade);
	for (_i = 1; _i < _test_index+1; _i++)
	{
		std::cout << "[Step " << _i << "] " << CMAGENTA << b << CRESET << std::endl;
		b.incrementGrade();
	}
}

void	Test::test_2(void)
{
	std::cout << BG_BRIGHT_CYAN << "[T]Test 2: Handled exception (safe test ✅ )"
			  << CRESET << " -> grade = " << _testGrade << ", steps = "
			  << _test_index << "." << std::endl;
	try
	{
		Bureaucrat b(_testName, _testGrade);
		for (_i = 1; _i < _test_index+1; _i++)
		{
			std::cout << "[Step " << _i << "] "
			  << CMAGENTA << b << CRESET << std::endl;
			b.incrementGrade();
		}
	}
	catch (std::exception &e) // only catch Bureaucrat exception -> catch (Bureaucrat::GradeTooHighException &e)
	{
		std::cout << CRED << e.what() << CRESET << std::endl;
	}
}

void	Test::test_3(void)
{
	std::cout << BG_BRIGHT_CYAN << "[T]Test 3: Incerement Test"
			  << CRESET << " -> grade = " << _testGrade << ", steps = "
			  << _test_index << "." << std::endl;
	try
	{
		Bureaucrat b(_testName, _testGrade);
		for (_i = 1; _i < _test_index+1; _i++)
		{
			std::cout << "[Step " << _i << "] "
			  << CMAGENTA << b << CRESET << std::endl;
			b.incrementGrade();
		}
	}
	catch(const std::exception& e)
	{
		std::cout << CRED << e.what() << CRESET << std::endl;
	}
}

void	Test::test_4(void)
{
	std::cout << BG_BRIGHT_CYAN << "[T]Test 4: Decrement Test"
			  << CRESET << " -> grade = " << _testGrade << ", steps = "
			  << _test_index << "." << std::endl;
	try
	{
		Bureaucrat b(_testName, _testGrade);
		for (_i = 1; _i < _test_index+1; _i++)
		{
			std::cout << "[Step " << _i << "] "
			  << CMAGENTA << b << CRESET << std::endl;
			b.decrementGrade();
		}
	}
	catch(const std::exception& e)
	{
		std::cout << CRED << e.what() << CRESET << std::endl;
	}
}

/******************************************************************************/
/*								EXCEPTIONS									  */
/******************************************************************************/
const char* Test::InvalidInput::what() const throw()
{
	return ("[TEST_EXCEPTION] Incorrect argv input format, chek the instructions!");
}

const char* Test::InvalidArgc::what() const throw()
{
	return ("[TEST_EXCEPTION] Incorrect argc number, check the instructions!");
}

const char* Test::InvalidTest::what() const throw()
{
	return ("[TEST_EXCEPTION] Incorrect test number, check the instructions!");
}

/******************************************************************************/
/*							GLOBAL FUNCTIONS								  */
/******************************************************************************/
void	showMsg(const char* color, const char* msg, const char* reset)
{
	std::cout << color << msg << reset << std::endl;
}
