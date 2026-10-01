/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RobotomyRequestForm.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 08:41:09 by mzolotar          #+#    #+#             */
/*   Updated: 2025/11/14 11:54:04 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RobotomyRequestForm.hpp"

/******************************************************************************/
/*						CONSTRUCTORS & DESTRUCTORS							  */
/******************************************************************************/
/*	Default Constructor		*/
RobotomyRequestForm::RobotomyRequestForm(void)
		:	AForm("RobotomyRequestForm", 72, 45),
			_target("default_target") {}

/*	Atribute Constructor	*/
RobotomyRequestForm::RobotomyRequestForm(const std::string &target)
		:	AForm("RobotomyRequestForm", 72, 45),
			_target(target) {}

/*	Copy Constructor		*/
RobotomyRequestForm::RobotomyRequestForm(const RobotomyRequestForm &other)
		:	AForm(other),
			_target(other._target) {}

/*	Desctructor				*/
RobotomyRequestForm::~RobotomyRequestForm() {}

/******************************************************************************/
/*								OPERATORS								  	  */
/******************************************************************************/
/*	Copy Assignment Operator	*/
RobotomyRequestForm& RobotomyRequestForm::operator=(const RobotomyRequestForm &other)
{
	if (this != &other)
	{
		AForm::operator=(other);
		this->_target = other._target;
	}
	return (*this);
}

/******************************************************************************/
/*								EXCEPTIONS									  */
/******************************************************************************/
const char *RobotomyRequestForm::RobotizationFailed::what() const throw()
{
	return ("[RobotomyRequestForm_EXCEPTION] Robotomy failed!");
}

/******************************************************************************/
/*							PUBLIC METHODS									  */
/******************************************************************************/
void	RobotomyRequestForm::beExecuted(Bureaucrat const &executor) const
{
	if (!getIsSigned())
		throw (AForm::AFormNotSignedException());
	if (executor.getGrade() > getExecuteGrade())
		throw (Bureaucrat::GradeTooLowException());
	
	int random_number;

	random_number = rand() % 2;

	if (random_number == 1)
		std::cout << "Beeep Be Be Beeeee Beeeeeeeep. " << this->getName() << " has been robotomized successfully!" << std::endl;
	else
		throw (RobotizationFailed());
}

/******************************************************************************/
/*							GLOBAL FUNCTIONS								  */
/******************************************************************************/
std::ostream&	operator<<(std::ostream& os, const RobotomyRequestForm& other)
{
	os << "[RobotomyRequestForm] Name: " << other.getName()
			  << " ,is signed by: " << other.getIsSigned()
			  << " , with sign grade: " << other.getSignGrade()
			  << " and execute grade: " << other.getExecuteGrade();
	return (os);
}
