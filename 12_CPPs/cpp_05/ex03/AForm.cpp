/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AForm.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 09:30:36 by mzolotar          #+#    #+#             */
/*   Updated: 2025/11/14 11:57:28 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AForm.hpp"

/******************************************************************************/
/*						CONSTRUCTORS & DESTRUCTORS							  */
/******************************************************************************/
/*	Default Constructor		*/
AForm::AForm(void) 
		:	_name("default_AForm"), _signed(false),
			_signGrade(LOWEST_GRADE), _execGrade(LOWEST_GRADE) {}

/*	Atribute Constructor	*/
AForm::AForm(std::string name, const int sign_grade, const int exec_grade)
		:	_name(name), _signed(false),
			_signGrade(sign_grade), _execGrade(exec_grade)
{
	if (this->_signGrade < HIGHEST_GRADE)
		throw (AForm::GradeTooHighException());
	else if (this->_signGrade > LOWEST_GRADE)
		throw (AForm::GradeTooLowException());
	if (this->_execGrade < HIGHEST_GRADE)
		throw (AForm::GradeTooHighException());
	else if (this->_execGrade > LOWEST_GRADE)
		throw (AForm::GradeTooLowException());

	std::cout << "[C]AForm Constructor." << std::endl;
}

/*	Copy Constructor		*/
AForm::AForm(const AForm& other)
		:	_name(other.getName() + "_copy"), _signed(false),
			_signGrade(other._signGrade), _execGrade(other._execGrade) {}

/*	Desctructor				*/
AForm::~AForm()
{
	std::cout << "[D]AForm Destructor." << std::endl;
}

/******************************************************************************/
/*								OPERATORS								  	  */
/******************************************************************************/
/*	Copy Assignment Operator	*/
AForm& AForm::operator=(const AForm& other)
{
	if (this != &other)
		this->_signed = other._signed;
	return (*this);
}

/******************************************************************************/
/*								GETTERS										  */
/******************************************************************************/
std::string const	AForm::getName(void) const
{
	return (this->_name);
}

bool	AForm::getIsSigned(void) const
{
	return (this->_signed);
}

int	AForm::getSignGrade(void) const
{
	return (this->_signGrade);
}

int	AForm::getExecuteGrade(void) const
{
	return (this->_execGrade);
}

/******************************************************************************/
/*								EXCEPTIONS									  */
/******************************************************************************/
const char *AForm::GradeTooHighException::what() const throw()
{
	return ("[AForm_EXCEPTION] Grade too high!");
}

const char* AForm::GradeTooLowException::what() const throw()
{
	return ("[AForm_EXCEPTION] Grade too Low!");
}

const char* AForm::AFormNotSignedException::what() const throw()
{
	return ("[AForm_EXCEPTION] Form needs to be signed before executing!");
}

/******************************************************************************/
/*							PUBLIC METHODS									  */
/******************************************************************************/
void	AForm::beSigned(Bureaucrat &signer)
{
	if (signer.getGrade() > this->_signGrade)
		throw (AForm::GradeTooLowException());
	else
	{
		this->_signed = true;
		std::cout << signer.getName() << " successfully signed "
				  << this->_name << std::endl;
	}
}

void	AForm::execute(Bureaucrat const &executor) const
{
	if (_signed == false)
		throw (AForm::AFormNotSignedException());
	if (_execGrade < executor.getGrade())
		throw (AForm::GradeTooLowException());

	beExecuted(executor);
}

void	AForm::beExecuted(Bureaucrat const &executor) const
{
	(void)executor;
}

/******************************************************************************/
/*							GLOBAL FUNCTIONS								  */
/******************************************************************************/
std::ostream&	operator<<(std::ostream& os, const AForm& other)
{
	os << "Name: " << other.getName()
			  << " ,is signed by: " << other.getIsSigned()
			  << " , with sign grade: " << other.getSignGrade()
			  << " and execute grade: " << other.getExecuteGrade();
	return (os);
}
