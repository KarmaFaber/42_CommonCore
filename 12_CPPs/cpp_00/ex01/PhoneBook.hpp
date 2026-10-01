/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 19:24:39 by mzolotar          #+#    #+#             */
/*   Updated: 2025/09/22 20:52:18 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHONEBOOK_HPP
#define PHONEBOOK_HPP

#include "header.hpp"
#include "Contact.hpp"
#include <string>
#include <iostream>
#include <cstdlib>

class PhoneBook
{
	private:
		Contact						_contacts[MAX_ID];
		int							_index;
		int							_contact_count;
		bool						_full_flag;
		static const std::string	_prompts[5];
		
		int			getValidIndex(std::string line) const;
		void		incrementIndex(void);
		std::string	getInput(std::string const prompt, std::string line);
		
		bool		isValidName(const std::string& name) const;
		bool		isValidNickname(const std::string& nickname) const;
		bool		isValidPhoneNumber(const std::string& phone) const;
		bool		isValidSecret(const std::string& secret) const;

		bool		validateField(int field_index, const std::string& input, std::string& error_msg) const;
		void		setContactField(Contact& contact, int field_index, const std::string& value) const;
		bool		processFieldInput(Contact& contact, int field_index, int& bad_input);

		bool		collectContactData(Contact& contact);

	public:
		PhoneBook(void);
		~PhoneBook();

		void	addContact(void);
		int		getLastIndex() const;
		bool	checkIndex(int index) const;
		void	printTable(void) const;
		void	printContact(int index) const;
		void	searchContact(void) const;
		void	showMsg(std::string color,std::string msg, std::string end_color) const;
		const Contact&	getContact(int index) const;
};

#endif