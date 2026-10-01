/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 10:48:10 by mzolotar          #+#    #+#             */
/*   Updated: 2025/11/14 11:22:35 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"


/******************************************************************************/
/*						CONSTRUCTORS & DESTRUCTORS							  */
/******************************************************************************/
/*	Default Constructor		*/
Bureaucrat::Bureaucrat(void) : _name("default_name"), _grade(LOWEST_GRADE) {}

/*	Atribute Constructor	*/
Bureaucrat::Bureaucrat(const std::string name, int grade)
			:  _name(name), _grade(LOWEST_GRADE)
{
	if(grade < HIGHEST_GRADE)
		throw GradeTooHighException();
	else if(grade > LOWEST_GRADE)
		throw GradeTooLowException();
	else
		this->_grade = grade;
	std::cout << "[C]Bureaucrat Constructor." << std::endl;
}

/*	Copy Constructor		*/
Bureaucrat::Bureaucrat(const Bureaucrat& other)
		:	_name(other.getName() + "_copi"), _grade(other._grade) {}
 
/*	Desctructor				*/
Bureaucrat::~Bureaucrat()
{
	std::cout << "[D]Bureaucrat Destructor." << std::endl;
}

/******************************************************************************/
/*								OPERATORS								  	  */
/******************************************************************************/
/*	Copy Assignment Operator	*/
Bureaucrat& Bureaucrat::operator=(const Bureaucrat& other)
{
	if (this != &other)
		this->_grade = other._grade;
	return (*this);
}

/******************************************************************************/
/*								GETTERS										  */
/******************************************************************************/
std::string	Bureaucrat::getName(void) const
{
	return (this->_name);
}

int	Bureaucrat::getGrade(void) const
{
	return (this->_grade);
}

/******************************************************************************/
/*								EXCEPTIONS									  */
/******************************************************************************/
const char *Bureaucrat::GradeTooHighException::what() const throw()
{
	return ("[BUREAUCRAT_EXCEPTION] Grade too high!");
}

const char* Bureaucrat::GradeTooLowException::what() const throw()
{
	return ("[BUREAUCRAT_EXCEPTION] Grade too Low!");
}

/******************************************************************************/
/*							PUBLIC FUNCTIONS								  */
/******************************************************************************/
void	Bureaucrat::incrementGrade(void)
{
	if (this->_grade <= HIGHEST_GRADE)
		throw (Bureaucrat::GradeTooHighException());
	this->_grade--;
	std::cout  << "[M] Bureaucrat incrementGrade method" << std::endl;
}

void	Bureaucrat::decrementGrade(void)
{
	if (this->_grade >= LOWEST_GRADE)
		throw (Bureaucrat::GradeTooLowException());
	this->_grade++;
	std::cout  << "[M] Bureaucrat decrementGrade method" << std::endl;
}

void	Bureaucrat::signForm(Form &form)
{
	try
	{
		form.beSigned(*this);
		std::cout << this->_name << " signs " << form.getName() << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << this->_name << " cannot sign " << form.getName()
				  << " because: " << e.what() << std::endl;
	}
}


/******************************************************************************/
/*							GLOBAL FUNCTIONS								  */
/******************************************************************************/
std::ostream&	operator<< ( std::ostream& os, const Bureaucrat& other)
{
	os << other.getName() << ", bureaucrat grade " << other.getGrade() << ".";
	return (os);
}
