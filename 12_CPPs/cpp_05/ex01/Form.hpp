/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 10:51:21 by mzolotar          #+#    #+#             */
/*   Updated: 2025/11/14 11:18:34 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FORM_HPP
#define FORM_HPP

#include <string>
#include <iostream>
#include <exception>
#include "Bureaucrat.hpp"

#define HIGHEST_GRADE	1
#define LOWEST_GRADE	150

class Bureaucrat;

class Form
{
	private:
		const std::string	_name;
		bool 				_signed;
		const int			_signGrade;
		const int			_execGrade;

	public:
		Form(void);
		Form(std::string name, const int sign_grade, const int exec_grade);
		Form(const Form& other);
		~Form();

		Form&	operator=(const Form& other);

		//getters
		std::string const	getName(void) const;
		bool				getIsSigned(void) const;
		int					getSignGrade(void) const;
		int					getExecuteGrade(void) const;

		//own method:
		void	beSigned(Bureaucrat &signer);

		//exceptions
		class GradeTooHighException : public std::exception
		{
			public:
				virtual const char* what() const throw();
		};
		class GradeTooLowException : public std::exception
		{
			public:
				virtual const char* what() const throw();
		};
};

std::ostream&	operator<<(std::ostream& os, const Form& other);

#endif
