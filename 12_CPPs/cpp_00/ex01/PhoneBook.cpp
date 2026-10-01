/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 19:24:25 by mzolotar          #+#    #+#             */
/*   Updated: 2025/09/22 21:08:09 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PhoneBook.hpp"
#include "header.hpp"

/******************************************************************************/
/*						CONSTRUCTORS & DESTRUCTORS							  */
/******************************************************************************/

/*	Constructor	*/ 
PhoneBook::PhoneBook(void) : _index(0), _contact_count(0), _full_flag(false) {}

/*	Desctructor	*/
PhoneBook::~PhoneBook() {}

/******************************************************************************/
/*								GETTERS										  */
/******************************************************************************/

const Contact& PhoneBook::getContact(int index) const
{
	return (_contacts[index]);
}

/******************************************************************************/
/*							PRIVATE FUNCTIONS								  */
/******************************************************************************/

const std::string PhoneBook::_prompts[5] = {
	"the first name",
	"the last name",
	"the nickname",
	"the phone number",
	"the darkest secret"
};

int PhoneBook::getValidIndex(std::string line) const
{
	for (size_t i = 0; i < line.length(); ++i)
	{
		if (!isdigit(line[i]))
		{
			return (-1);
		}
	}
	return (atoi(line.c_str()));
}

void PhoneBook::incrementIndex(void)
{
	_index++;
	if (!_full_flag)
	{
		_contact_count++;
	}
	if (_index >= MAX_ID)
	{
		_index = 0;
		_full_flag = true;
	}
}

std::string	PhoneBook::getInput(std::string const prompt, std::string line)
{
	std::cout << "Please enter " << prompt << ": " << std::endl << "> ";
	if (!std::getline(std::cin, line) || std::cin.eof())
	{
		showMsg(CBLACK, MSG_EOF, CRESET);
		return(std::string());
	}
	return (line);
}

bool PhoneBook::isValidName(const std::string& name) const
{
	if (name.empty())
		return (false);
		
	for (size_t i = 0; i < name.length(); ++i)
	{
		if (!isalpha(name[i]) && name[i] != ' ' && name[i] != '-' && name[i] != '\'')
			return (false);
	}
	return (true);
}

bool PhoneBook::isValidNickname(const std::string& nickname) const
{
	if (nickname.empty())
		return (false);
		
	for (size_t i = 0; i < nickname.length(); ++i)
	{
		if (!isalnum(nickname[i]) && nickname[i] != '_' && nickname[i] != '-')
			return (false);
	}
	return (true);
}

bool PhoneBook::isValidPhoneNumber(const std::string& phone) const
{
	if (phone.empty())
		return (false);
		
	for (size_t i = 0; i < phone.length(); ++i)
	{
		if (!isdigit(phone[i]))
			return (false);
	}
	return (true);
}

bool PhoneBook::isValidSecret(const std::string& secret) const
{
	if (secret.empty())
		return (false);
		
	for (size_t i = 0; i < secret.length(); ++i)
	{
		if (iscntrl(secret[i]) && secret[i] != '\t')
			return (false);
	}
	return (true);
}

bool PhoneBook::validateField(int field_index, const std::string& input, std::string& error_msg) const
{
	switch (field_index)
	{
		case 0:
			if (!isValidName(input))
			{
				error_msg = INVALID_FNAME;
				return (false);
			}
			break;
		case 1:
			if (!isValidName(input))
			{
				error_msg = INVALID_NAME;
				return (false);
			}
			break;
		case 2:
			if (!isValidNickname(input))
			{
				error_msg = INVALID_NICKNAME;
				return (false);
			}
			break;
		case 3:
			if (!isValidPhoneNumber(input))
			{
				error_msg = INVALID_NUMBER;
				return (false);
			}
			break;
		case 4:
			if (!isValidSecret(input))
			{
				error_msg = INVALID_SECRET;
				return (false);
			}
			break;
	}
	return (true);
}

void PhoneBook::setContactField(Contact& contact, int field_index, const std::string& value) const
{
	switch (field_index)
	{
		case 0: contact.setFirstName(value);
			break;
		case 1: contact.setLastName(value);
			break;
		case 2: contact.setNickName(value);
			break;
		case 3: contact.setPhoneNumber(value);
			break;
		case 4: contact.setSecret(value);
			break;
	}
}

bool PhoneBook::processFieldInput(Contact& contact, int field_index, int& bad_input)
{
	std::string line;
	std::string error_msg;
		
	while (true)
	{
		line = getInput(_prompts[field_index], line);
		if (line.empty() && std::cin.eof())
			return (false);
			
		if (line.empty())
		{
			bad_input++;
			showMsg(CRED, INVALID_INPUT, CRESET);
			if (bad_input >= MAX_ATTEMPTS)
			{
				showMsg(CBLACK, MSG_BAD_INPUT, CRESET);
				return (false);
			}
			continue;
		}
		
		if (!validateField(field_index, line, error_msg))
		{
			bad_input++;
			showMsg(CRED, error_msg, CRESET);
			if (bad_input >= MAX_ATTEMPTS)
			{
				showMsg(CBLACK, MSG_BAD_INPUT, CRESET);
				return (false);
			}
			continue;
		}
		
		bad_input = 0;
		setContactField(contact, field_index, line);
		break;
	}
	return (true);
}

bool PhoneBook::collectContactData(Contact& contact)
{
	int bad_input = 0;
		
	for (int i = 0; i < 5; i++)
	{
		if (!processFieldInput(contact, i, bad_input))
			return (false);
	}
	return (true);
}

/******************************************************************************/
/*							PUBLIC FUNCTIONS								  */
/******************************************************************************/

void PhoneBook::addContact(void)
{
	showMsg(CBLUE, "+------------ New Contact Menu -------------+", CRESET);
	if (_index < MAX_ID)
	{
		std::cout << "This is your contact #" << _index + 1 << std::endl;
	} 
	else if (_index == MAX_ID && _full_flag)
	{
		showMsg(CRED, MSG_FULL, CRESET);
		_index = 0;
	}
	Contact &contact = _contacts[_index];
	if (!collectContactData(contact))
	{
		return ;
	}
	incrementIndex();
	showMsg(CBLACK, MSG_SAVE, CRESET);
}

int PhoneBook::getLastIndex() const
{
	if (_full_flag)
		return (MAX_ID);
	return (_contact_count);
}

bool PhoneBook::checkIndex(int index) const
{
	if (index == 0)
	{
		showMsg(CBLACK, MSG_QUIT , CRESET);
		return (false);
	}
	if (index < 1 || index > MAX_ID)
	{
		showMsg(CRED, INVALID_INDEX, CRESET);
		return (false);
	}
	if (index > getLastIndex())
	{
		showMsg(CRED, INVALID_CONT, CRESET);
		return (false);
	}
	return (true);
}

void PhoneBook::printTable(void) const
{
	int limit = getLastIndex();

	std::cout << TABLE_START << std::endl;
	std::cout << TABLE_INDEX << std::endl;
	std::cout << TABLE_MID << std::endl;
	for (int i = 0; i < limit; i++)
	{
		getContact(i).printRow(i + 1);
	}
	std::cout << TABLE_END << std::endl;
}

void PhoneBook::printContact(int index) const
{
	const Contact& contact = getContact(index - 1);
	std::cout << std::endl;
	std::cout << "Contact #" << index << " details:" << std::endl;
	std::cout << "------------------------" << std::endl;
	std::cout << "First name: " << CGREEN << contact.getFirstName()
		<< CRESET << std::endl;
	std::cout << "Last name: " << CGREEN << contact.getLastName()
		<< CRESET << std::endl;
	std::cout << "Nickname: " << CGREEN << contact.getNickName()
		<< CRESET << std::endl;
	std::cout << "Phone number: " << CGREEN << contact.getNumber()
		<< CRESET << std::endl;
	std::cout << "Darkest secret: " << CGREEN << contact.getSecret()
		<< CRESET << std::endl;
	std::cout << std::endl;
}

void PhoneBook::searchContact(void) const
{
	int bad_input = 0;

	if (_contact_count == 0)
	{
		showMsg(CRED, MSG_EMPTY, CRESET);
		return ;
	}
	std::string line;
	while (true)
	{
		showMsg(CBLUE, MSG_INSTRUCT, CRESET);
		printTable();
		if (!std::getline(std::cin, line))
		{
			showMsg(CBLACK, MSG_EOF, CRESET);
			break;
		}
		if (line == "0")
		{
			showMsg(CBLACK, MSG_QUIT, CRESET);
			break;
		}
		int index = getValidIndex(line);
		if (index == -1 || !checkIndex(index))
		{
			bad_input++;
			showMsg(CRED, INVALID_INPUT, CRESET);
		}
		else {
			bad_input = 0;
			printContact(index);
		}
		if (bad_input >= 3)
		{
			showMsg(CBLACK, MSG_BAD_INPUT, CRESET);
			break;
		}
	}
}

void PhoneBook::showMsg(std::string color, std::string msg, std::string end_color)const
{
	std::cout << color << msg << end_color << std::endl;
}
