/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Intern.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 13:12:11 by mzolotar          #+#    #+#             */
/*   Updated: 2025/11/14 11:55:35 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Intern.hpp"

/******************************************************************************/
/*						CONSTRUCTORS & DESTRUCTORS							  */
/******************************************************************************/
/*	Default Constructor		*/
Intern::Intern(void) {}

/*	Copy Constructor		*/
Intern::Intern(const Intern &other)
{
	(void)other;
}

/*	Desctructor				*/
Intern::~Intern() {}

/******************************************************************************/
/*								OPERATORS								  	  */
/******************************************************************************/
/*	Copy Assignment Operator	*/
Intern &Intern::operator=(const Intern &other)
{
	(void) other;
	return (*this);
}

/******************************************************************************/
/*								EXCEPTIONS									  */
/******************************************************************************/
const char *Intern::InvalidFormException::what() const throw()
{
	return ("[INTERN_EXCEPTION] Form name does not exist.!");
}


/******************************************************************************/
/*							PUBLIC METHODS									  */
/******************************************************************************/
AForm *Intern::makeForm(const std::string form_name, const std::string form_target)
{
	int i = 0;
	std::string available_forms[] = {"ShrubberyCreationForm", "RobotomyRequestForm", "PresidentialPardonForm"};

	while (i < 3 && form_name != available_forms[i])
		i++;
	
	switch (i)
	{
	case 0:
		std::cout << "Intern creates " << form_name << std::endl;
		return (new ShrubberyCreationForm(form_target));
	case 1:
		std::cout << "Intern creates " << form_name << std::endl;
		return (new RobotomyRequestForm(form_name));
	case 2:
		std::cout << "Intern creates " << form_name << std::endl;
		return (new PresidentialPardonForm (form_target));
	default:
		std::cout << "Intern cannot create " << form_name << std::endl;
		throw (InvalidFormException());
		//return NULL;
	}
}
