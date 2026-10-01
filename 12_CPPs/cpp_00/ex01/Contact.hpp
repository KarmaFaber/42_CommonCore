/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 19:24:32 by mzolotar          #+#    #+#             */
/*   Updated: 2025/09/22 20:29:46 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTACT_HPP
# define CONTACT_HPP

#include "header.hpp"
#include <string>
#include <iostream>
#include <iomanip>

class Contact
{
	private:
		std::string	_first_name;
		std::string	_last_name;
		std::string	_nick_name;
		std::string	_phone_number;
		std::string	_darkest_secret;

		std::string	formatField(const std::string& str) const;

	public:
		Contact(void);
		~Contact();

		const std::string&	getFirstName(void) const;
		const std::string&	getLastName(void) const;
		const std::string&	getNickName(void) const;
		const std::string&	getNumber(void) const;
		const std::string&	getSecret(void) const;

		void	setFirstName(const std::string& str_f_name);
		void	setLastName(const std::string& str_l_name);
		void	setNickName(const std::string& str_nick_name);
		void	setPhoneNumber(const std::string& number);
		void	setSecret(const std::string& str_secret);

		void	printRow(int index) const;
};

#endif