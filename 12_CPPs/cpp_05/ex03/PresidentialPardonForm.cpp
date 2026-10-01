/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PresidentialPardonForm.cpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 08:39:07 by mzolotar          #+#    #+#             */
/*   Updated: 2025/11/14 11:54:35 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PresidentialPardonForm.hpp"

/******************************************************************************/
/*						CONSTRUCTORS & DESTRUCTORS							  */
/******************************************************************************/
/*	Default Constructor		*/
PresidentialPardonForm::PresidentialPardonForm()
		:	AForm("PresidentialPardonForm", 25, 5),
			_target("default_target") {}

/*	Atribute Constructor	*/
PresidentialPardonForm::PresidentialPardonForm(const std::string &target)
		:	AForm("PresidentialPardonForm", 25, 5),
			_target(target) {}

/*	Copy Constructor		*/
PresidentialPardonForm::PresidentialPardonForm(const PresidentialPardonForm &other)
		:	AForm(other),
			_target(other._target) {}

/*	Desctructor				*/
PresidentialPardonForm::~PresidentialPardonForm() {}

/******************************************************************************/
/*								OPERATORS								  	  */
/******************************************************************************/
/*	Copy Assignment Operator	*/
PresidentialPardonForm& PresidentialPardonForm::operator=(const PresidentialPardonForm &other)
{
	if (this != &other)
	{
		AForm::operator=(other);
		this->_target = other._target;
	}
	return (*this);
}

/******************************************************************************/
/*							PUBLIC METHODS									  */
/******************************************************************************/
void	PresidentialPardonForm::beExecuted(Bureaucrat const &executor) const
{
	(void)executor;
	std::cout << this->getName() << " has been pardoned by Zaphod Beeblebrox" << std::endl;
}

/******************************************************************************/
/*							GLOBAL FUNCTIONS								  */
/******************************************************************************/
std::ostream&	operator<<(std::ostream& os, const PresidentialPardonForm& other)
{
	os << "[ShrubberyCreationForm] Name: "
			  << other.getName() << " ,is signed by: " << other.getIsSigned()
			  << " , with sign grade: " << other.getSignGrade()
			  << " and execute grade: " << other.getExecuteGrade();
	return (os);
}
