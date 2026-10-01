/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShrubberyCreationForm.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 08:41:11 by mzolotar          #+#    #+#             */
/*   Updated: 2025/11/14 11:44:02 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ShrubberyCreationForm.hpp"

/******************************************************************************/
/*						CONSTRUCTORS & DESTRUCTORS							  */
/******************************************************************************/
/*	Default Constructor		*/
ShrubberyCreationForm::ShrubberyCreationForm(void)
		:	AForm("ShrubberyCreationForm", 145, 137),
			_target("default_target") {}

/*	Atribute Constructor	*/
ShrubberyCreationForm::ShrubberyCreationForm(const std::string &target)
		:	AForm("ShrubberyCreationForm", 145, 137),
			_target(target) {}

/*	Copy Constructor		*/
ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm &other)
		:	AForm(other),
			_target(other._target) {}

/*	Desctructor				*/
ShrubberyCreationForm::~ShrubberyCreationForm() {}

/******************************************************************************/
/*								OPERATORS								  	  */
/******************************************************************************/
/*	Copy Assignment Operator	*/
ShrubberyCreationForm& ShrubberyCreationForm::operator=(const ShrubberyCreationForm &other)
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
const char *ShrubberyCreationForm::OpenFileException::what() const throw()
{
	return ("[ShrubberyCreationForm_EXCEPTION] Could not open and write the file!");
}

/******************************************************************************/
/*							PRIVATE METHODS									  */
/******************************************************************************/
void ShrubberyCreationForm::printTree(std::ofstream &outfile) const
{
	outfile <<
	"                                  # #### ####\n"
	"                                ### \\/#|### |/####\n"
	"                               ##\\/#/ \\||/##/_/##/_#\n"
	"                             ###  \\/###|/ \\/ # ###\n"
	"                           ##_\\_#\\_\\## | #/###_/_####\n"
	"                          ## #### # \\ #| /  #### ##/##\n"
	"                           __#_--###`  ||,###---###-~\n"
	"                                     \\ ||\n"
	"                                      |||\n"
	"                                      |||\n"
	"                                      ||||\n"
	"                                , -=-~| .-^- _\n"
	"                                      `|\n"
	"                                       |\n"
	<< std::endl;
}

/******************************************************************************/
/*							PUBLIC METHODS									  */
/******************************************************************************/
void	ShrubberyCreationForm::beExecuted(Bureaucrat const &executor) const
{
	if (!getIsSigned())
		throw (AForm::AFormNotSignedException());
	if (executor.getGrade() > getExecuteGrade())
		throw (Bureaucrat::GradeTooLowException());

	std::ofstream outfile((_target + "_shrubbery").c_str());
	if (!outfile.is_open() || outfile.fail())
		throw (ShrubberyCreationForm::OpenFileException());

	printTree(outfile);
	outfile.close();

	std::cout << executor.getName()
			  << " successfully created a shrubbery 🌳" << std::endl;
}

/******************************************************************************/
/*							GLOBAL FUNCTIONS								  */
/******************************************************************************/

std::ostream&	operator<<(std::ostream& os, const ShrubberyCreationForm& other)
{
	os << "[ShrubberyCreationForm] Name: " << other.getName()
			  << " ,is signed by: " << other.getIsSigned()
			  << " , with sign grade: " << other.getSignGrade()
			  << " and execute grade: " << other.getExecuteGrade();
	return (os);
}
