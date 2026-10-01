/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AForm.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 10:51:21 by mzolotar          #+#    #+#             */
/*   Updated: 2025/11/14 11:40:37 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AFORM_HPP
#define AFORM_HPP

#include <string>
#include <iostream>
#include <exception>
#include "Bureaucrat.hpp"

#define HIGHEST_GRADE	1
#define LOWEST_GRADE	150

class Bureaucrat;

class AForm
{
	private:
		const std::string	_name;
		bool 				_signed;
		const int			_signGrade;
		const int			_execGrade;
	public:
		AForm(void);
		AForm(std::string name, const int sign_grade, const int exec_grade);
		AForm(const AForm& other);
		AForm& operator=(const AForm& other);
		virtual	~AForm();

		std::string const	getName(void) const;
		bool				getIsSigned(void) const;
		int					getSignGrade(void) const;
		int					getExecuteGrade(void) const;

		void				beSigned(Bureaucrat &signer);

		void				execute(Bureaucrat const &executor) const;
		virtual void		beExecuted(Bureaucrat const &executor) const = 0;

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
		class AFormNotSignedException : public std::exception
		{
		public:
			virtual const char *what() const throw();
		};
};

std::ostream&	operator<<(std::ostream& os, const AForm& other);

#endif
