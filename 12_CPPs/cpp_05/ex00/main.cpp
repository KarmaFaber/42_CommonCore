/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 10:47:56 by mzolotar          #+#    #+#             */
/*   Updated: 2025/11/14 10:41:40 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Test.hpp"

int main(int argc, char** argv)
{
	try
	{
		Test t(argc, argv);
		t.runTest();
		showMsg(CYELLOW, "\n\nIf test catch is executed, this code should be printed..", CRESET);
	}
	catch (const std::exception& e)
	{
		if (dynamic_cast<const Test::InvalidInput*>(&e) ||
			dynamic_cast<const Test::InvalidArgc*>(&e) ||
			dynamic_cast<const Test::InvalidTest*>(&e))
		{
			showMsg(CRED, "e.what() in main -> test exceptions", CRESET);
			showMsg(CRED, e.what(), CRESET);
			return (1);
		}

		if (dynamic_cast<const Bureaucrat::GradeTooHighException*>(&e) ||
			dynamic_cast<const Bureaucrat::GradeTooLowException*>(&e))
		{
			showMsg(CRED, "e.what() in main -> Bureaucrat exceptions", CRESET);
			showMsg(CRED, e.what(), CRESET);
			return (2);
		}

		showMsg(CRED, "[MAIN_TEST_EXCEPTION] Unhandled std::exception!", CRESET);
		return (3);
	}
	
	showMsg(CGREEN, "\n\nmain continues to execute code after running the test, with and without exceptions.", CRESET);
	showMsg(CGREEN, "Check this part in the defense: how the program works in C++ when we use exceptions\n", CRESET);
	
	return (0);
}

//Try this main() -> ⚠️ This main will have segfoults, but that's part of the design of this test. ⚠️
/*
int main(int argc, char** argv)
{
	showMsg(CGREEN, "\nAn exception interrupts the normal flow of execution when an error or exceptional situation occurs.", CRESET);
	showMsg(CGREEN, "The program jumps abruptly from the point of the THROW to the FIRST CATCH that can handle that exception.", CRESET);
	showMsg(CGREEN, "The program continues from the catch block or, if there is no suitable catch, std::terminate() is called and the program terminates.", CRESET);
	showMsg(CGREEN, "See what happens if we have exceptions but no catch to handle them.", CRESET);
	showMsg(CGREEN, "See results of Test ARGC (./exceptions 1 12 -ksdnklsd 2) and Test 1 (./exceptions 1 Azazel -10 2).", CRESET);
	showMsg(CGREEN, "\ntesting std::terminate();", CRESET);

	Test t(argc, argv);
	t.runTest();

	showMsg(CGREEN, "\n\nmain continues to execute code after running the test, with and without exceptions.", CRESET);
	showMsg(CGREEN, "Check this part in the defense: how the program works in C++ when we use exceptions.", CRESET);
	
	return (0);
}
*/

/*
int main()
{
	std::cout << "\n/++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/\n";
	std::cout << "/+                              Running internal tests                          +/\n";
	std::cout << "/++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/\n\n";

	const char* tests[][5] = {
		{"./exceptions", "1", "Azazel", "-10", "2"},
		{"./exceptions", "1", "Azazel", "0", "2"},
		{"./exceptions", "1", "Azazel", "2", "2"},
		{"./exceptions", "1", "Azazel", "151", "2"},
		{"./exceptions", "2", "Vetala", "2", "2"},
		{"./exceptions", "2", "Vetala", "5", "2"},
		{"./exceptions", "3", "Pazuzu", "3", "5"},
		{"./exceptions", "4", "Oni", "140", "148"},
		{"./exceptions", "4", "Oni", "140", "5"}
	};

	for (int i = 0; i < 9; ++i)
	{
		try
		{
			Test t(5, const_cast<char**>(tests[i]));
			t.runTest();
		}
		catch (const std::exception& e)
		{
			// capturamos las excepciones esperadas
			if (dynamic_cast<const Test::InvalidArgc*>(&e) ||
				dynamic_cast<const Test::InvalidInput*>(&e) ||
				dynamic_cast<const Test::InvalidTest*>(&e))
				showMsg(CRED, e.what(), CRESET);

			else if (dynamic_cast<const Bureaucrat::GradeTooHighException*>(&e) ||
					 dynamic_cast<const Bureaucrat::GradeTooLowException*>(&e))
				showMsg(CRED, e.what(), CRESET);

			else
				showMsg(CRED, "[MAIN_TEST_EXCEPTION] Unhandled std::exception!", CRESET);

			continue;
		}
	}

	showMsg(CGREEN, "\n[END] All tests executed.", CRESET);
	return (0);
}
*/
