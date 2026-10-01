/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Test.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 10:55:44 by mzolotar          #+#    #+#             */
/*   Updated: 2025/11/14 11:03:09 by mzolotar         ###   ########.fr       */
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

#define TETS_NUM_MIN			1
#define TETS_NUM_MAX			4

#define MAX_GRADE_ALOW			1
#define MIN_GRADE_ALOW			150

#define TETS_INDEX_DEFAULT		1
#define TETS_INDEX_MIN			1
#define TETS_INDEX_MAX			200

#include <iostream>
#include <cstdlib>
#include <exception>
#include <cstring>

#include "Bureaucrat.hpp"

class Test
{
	private:
		int			_test_num;			// -> (argv[1]) -> isdigit
		std::string	_testName;			// -> (argv[2]) -> isalpha
		int			_testGrade;			// -> (argv[3]) -> isdigit + checkrank (1-150)
		int			_test_index;		// -> (argv[4]) 
		int			_i;					// -> isdigit + >=1 & <200

		bool validateTestNum(char **argv);
		bool validateName(char **argv);
		bool validateGrade(char **argv);
		bool validateTestIndex(char **argv);
		bool validateArgv(char **argv);

	public:
		Test(int argc, char **argv);
		~Test();

		void			runTest(void);
		void			test_1(void);
		void			test_2(void);
		void			test_3(void);
		void			test_4(void);
		
		class InvalidInput : public std::exception
		{
			public:
				virtual const char *what() const throw();
		};
		class InvalidArgc : public std::exception
		{
			public:
				virtual const char *what() const throw();
		};
		class InvalidTest : public std::exception
		{
			public:
				virtual const char *what() const throw();
		};
};

void	showMsg(const char* color, const char* msg, const char* reset);

#endif
