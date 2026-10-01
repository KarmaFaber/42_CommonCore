/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 10:48:22 by mzolotar          #+#    #+#             */
/*   Updated: 2025/11/14 11:19:56 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Form.hpp"

/******************************************************************************/
/*						CONSTRUCTORS & DESTRUCTORS							  */
/******************************************************************************/
/*	Default Constructor		*/
Form::Form(void) 
		:	_name("default_form"), _signed(false),
			_signGrade(LOWEST_GRADE), _execGrade(LOWEST_GRADE) {}

/*	Atribute Constructor	*/
Form::Form(std::string name, const int sign_grade, const int exec_grade)
		:	_name(name), _signed(false),
			_signGrade(sign_grade), _execGrade(exec_grade)
{
	if (this->_signGrade < HIGHEST_GRADE)
		throw (Form::GradeTooHighException());
	else if (this->_signGrade > LOWEST_GRADE)
		throw (Form::GradeTooLowException());
	if (this->_execGrade < HIGHEST_GRADE)
		throw (Form::GradeTooHighException());
	else if (this->_execGrade > LOWEST_GRADE)
		throw (Form::GradeTooLowException());

	std::cout << "[C]Form Constructor." << std::endl;
}

/*	Copy Constructor		*/
Form::Form(const Form& other)
		:	_name(other.getName() + "_copy"), _signed(false),
			_signGrade(other._signGrade), _execGrade(other._execGrade) {}

/*	Desctructor				*/
Form::~Form()
{
	std::cout << "[D]Form Destructor." << std::endl;
}

/******************************************************************************/
/*								OPERATORS								  	  */
/******************************************************************************/
/*	Copy Assignment Operator	*/
Form& Form::operator=(const Form& other)
{
	if (this != &other)
		this->_signed = other._signed;
	return (*this);
}

/******************************************************************************/
/*								GETTERS										  */
/******************************************************************************/
std::string const	Form::getName(void) const
{
	return (this->_name);
}

bool	Form::getIsSigned(void) const
{
	return (this->_signed);
}

int	Form::getSignGrade(void) const
{
	return (this->_signGrade);
}

int	Form::getExecuteGrade(void) const
{
	return (this->_execGrade);
}

/******************************************************************************/
/*								EXCEPTIONS									  */
/******************************************************************************/
const char *Form::GradeTooHighException::what() const throw()
{
	return ("[FORM_EXCEPTION] Grade too high!");
}

const char* Form::GradeTooLowException::what() const throw()
{
	return ("[FORM_EXCEPTION] Grade too Low!");
}

/******************************************************************************/
/*							PUBLIC METHODS									  */
/******************************************************************************/
void	Form::beSigned(Bureaucrat &signer)
{
	if (signer.getGrade() > this->_signGrade)
		throw (Form::GradeTooLowException());
	else
	{
		this->_signed = true;
		std::cout << signer.getName() << " successfully signed "
				  << this->_name << std::endl;
	}
}

/******************************************************************************/
/*							GLOBAL FUNCTIONS								  */
/******************************************************************************/
std::ostream&	operator<<(std::ostream& os, const Form& other)
{
	os << "Name: " << other.getName() << " ,is signed by: " << other.getIsSigned()
			  << " , with sign grade: " << other.getSignGrade()
			  << " and execute grade: " << other.getExecuteGrade();
	return (os);
}
