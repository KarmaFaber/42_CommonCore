/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 11:08:26 by mzolotar          #+#    #+#             */
/*   Updated: 2025/11/14 11:24:19 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Form.hpp"
#include "Bureaucrat.hpp"

#define CYELLOW				"\033[0;33m"
#define CMAGENTA			"\033[0;35m"
#define CRED				"\033[0;31m"
#define CRESET				"\033[0m"

int main(void)
{
	try
	{
		std::cout << CMAGENTA << "\n=== Test 1: Create valid Bureaucrat and Form ===" << CRESET << std::endl;
		Bureaucrat b("Notaryx", 140);
		Form f("Form_404", 75, 55);

		std::cout << CYELLOW << b << CRESET << std::endl;
		std::cout << CYELLOW << f << CRESET << std::endl;

		std::cout << CMAGENTA << "\n=== Test 2: The bureaucrat attempts to sign (failure) ===" << CRESET << std::endl;
		b.signForm(f);
		std::cout << CYELLOW << f << CRESET << std::endl;

		std::cout << CMAGENTA << "\n=== Test 3: Move up a grade and try again ===" << CRESET << std::endl;
		for (int i = 0; i < 11; ++i)
			b.decrementGrade();			//<- Bureaucrat::GradeTooLowException()

		std::cout << CMAGENTA << "\n=== Test 4: sign and besigned ===" << CRESET << std::endl;
		std::cout << CMAGENTA << "b.signForm(f):" << CRESET << std::endl;
		std::cout << CYELLOW << b << CRESET << std::endl;
		b.signForm(f);
		std::cout << CYELLOW << f << CRESET << std::endl;

		std::cout << CMAGENTA << "\nf.beSigned(b);" << CRESET << std::endl;
		std::cout << CYELLOW << b << CRESET << std::endl;
		f.beSigned(b);					//<- Form::GradeTooLowException()
		std::cout << CYELLOW << f << CRESET << std::endl;

	}
	catch (const std::exception &e)
	{
		std::cout << CRED << "\n❌ Exception caught: " << e.what() << CRESET << std::endl;
	}
	std::cout << CMAGENTA << "\nmain continues to execute the program\n" << CRESET << std::endl;
	return 0;
}

//Try this main() -> ⚠️ This main will have segfoults, but that's part of the design of this test. ⚠️
/*
int main(void)
{
	try
	{
		Bureaucrat b ("Notaryx", 2);
		b.incrementGrade();
		b.incrementGrade();
	}
	catch(Bureaucrat::GradeTooLowException &e)
	{
		std::cout << CRED << e.what() << CRESET << std::endl;
	}
	std::cout << CMAGENTA << "\nmain continues to execute the program\n" << CRESET << std::endl;
	return (0);
}
*/

//Try this main() -> ⚠️ This main will have segfoults, but that's part of the design of this test. ⚠️
/*
int main(void)
{

	std::cout << CMAGENTA << "\n=== Test 1: Create valid Bureaucrat and Form ===" << CRESET << std::endl;
	Bureaucrat b("Notaryx", 140);
	Form f("Form_404", 75, 55);

	std::cout << CYELLOW << b << CRESET << std::endl;
	std::cout << CYELLOW << f << CRESET << std::endl;

	std::cout << CMAGENTA << "\n=== Test 2: The bureaucrat attempts to sign (failure) ===" << CRESET << std::endl;
	b.signForm(f);
	std::cout << CYELLOW << f << CRESET << std::endl;

	std::cout << CMAGENTA << "\n=== Test 3: Move down a grade and try again ===" << CRESET << std::endl;
	for (int i = 0; i < 11; ++i)
		b.decrementGrade();

	std::cout << "   " << std::endl;
	std::cout << CYELLOW << b << CRESET << std::endl;
	b.signForm(f);
	std::cout << CYELLOW << f << CRESET << std::endl;


	std::cout << CMAGENTA << "\nmain continues to execute the program\n" << CRESET << std::endl;
	return 0;
}
*/
