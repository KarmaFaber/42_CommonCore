/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 19:24:35 by mzolotar          #+#    #+#             */
/*   Updated: 2025/09/22 20:28:53 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Contact.hpp"

/******************************************************************************/
/*						CONSTRUCTORS & DESTRUCTORS							  */
/******************************************************************************/

/*	Constructor	*/
Contact::Contact(void): _first_name(""),
						_last_name(""),
						_nick_name(""),
						_phone_number(""),
						_darkest_secret("") {}

/*	Desctructor	*/
Contact::~Contact() {}

/******************************************************************************/
/*								GETTERS										  */
/******************************************************************************/

const std::string& Contact::getFirstName(void) const
{
	return (_first_name);
}

const std::string& Contact::getLastName(void) const
{
	return (_last_name);
}

const std::string& Contact::getNickName(void) const
{
	return (_nick_name);
}

const std::string& Contact::getNumber(void) const
{
	return (_phone_number);
}

const std::string& Contact::getSecret(void) const
{
	return (_darkest_secret);
}

/******************************************************************************/
/*								SETTERS										  */
/******************************************************************************/

void	Contact::setFirstName(const std::string& str_f_name)
{
	_first_name = str_f_name;
}

void	Contact::setLastName(const std::string& str_l_name)
{
	_last_name = str_l_name;
}

void	Contact::setNickName(const std::string& str_nick_name)
{
	_nick_name = str_nick_name;
}

void	Contact::setPhoneNumber(const std::string& number)
{
	_phone_number = number;
}

void	Contact::setSecret(const std::string& str_secret)
{
	_darkest_secret = str_secret;
}

/******************************************************************************/
/*							PRIVATE FUNCTIONS								  */
/******************************************************************************/

std::string	Contact::formatField(const std::string& str) const
{
	if (str.length() > 10)
		return (str.substr(0, 9) + ".");
	return (std::string(10 - str.length(), ' ') + str);
}

/******************************************************************************/
/*							PUBLIC FUNCTIONS								  */
/******************************************************************************/

void Contact::printRow(int index) const
{
	std::cout << "║" << CGREEN  << std::setw(10) << index << CRESET
			  << "│" << CGREEN  << formatField(_first_name) << CRESET
			  << "│" << CGREEN  << formatField(_last_name) << CRESET
			  << "│" << CGREEN  << formatField(_nick_name) << CRESET
			  << "║" << std::endl;
}
