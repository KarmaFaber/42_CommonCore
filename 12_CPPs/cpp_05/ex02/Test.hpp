/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Test.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 10:55:44 by mzolotar          #+#    #+#             */
/*   Updated: 2025/11/03 12:53:56 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_HPP
#define TEST_HPP

#define CRED				"\033[0;31m"
#define CBLACK				"\033[0;30m"
#define CBLUE				"\033[0;34m"
#define CGREEN				"\033[0;32m"
#define CYELLOW				"\033[0;33m"
#define CMAGENTA			"\033[0;35m"
#define CCYAN				"\e[36m"
#define BG_BRIGHT_CYAN		"\e[106m"
#define BG_BRIGHT_YELLOW	"\e[103m"
#define CRESET				"\033[0m"

#include <iostream>
#include <cstdlib>
#include <exception>
#include <cstring>

#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

class Test
{
	public:
		bool	findTest(char** argv);
		void	test_1(void);
		void	test_2(void);
		void	test_3(void);
		void	test_4(void);
		void	test_5(void);
		
		class InvalidInput : public std::exception
		{
			public:
				virtual const char *what() const throw();
		};
};

void	showMsg(const char* color, const char* msg, const char* reset);
void	testUse(void);

#endif
