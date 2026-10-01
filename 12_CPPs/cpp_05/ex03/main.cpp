/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 10:47:56 by mzolotar          #+#    #+#             */
/*   Updated: 2025/11/14 11:51:08 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Test.hpp"

int main(int argc, char** argv)
{
	try
	{
		if (argc != 2)
			throw (Test::InvalidInput());
		Test t;
		t.findTest(argv);
	}
	catch (const Test::InvalidInput& e)
	{
		showMsg(CRED, e.what(), CRESET);
		testUse();
		return (1);
	}
	catch (const std::exception& e)
	{
		showMsg(CRED, e.what(), CRESET);
		return (2);
	}
	showMsg(CGREEN, "\n\nmain continues to execute code after running the test, with and without exceptions.", CRESET);
	showMsg(CGREEN, "Check this part in the defense: how the program works in C++ when we use exceptions.\n", CRESET);
	return (0);
}
