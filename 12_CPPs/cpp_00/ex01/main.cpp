/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 11:35:05 by mzolotar          #+#    #+#             */
/*   Updated: 2025/09/22 20:12:24 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PhoneBook.hpp"
#include "header.hpp"

int main (void)
{
	PhoneBook	book_obj;
	std::string	str;

	while (true)
	{
		book_obj.showMsg(CBLUE, INSTRUCTIONS, CRESET);
		if (!std::getline(std::cin, str))
		{
			book_obj.showMsg(CBLACK, MSG_EOF, CRESET);
			break;
		}
		if (str == "ADD")
		{
			book_obj.addContact();
			if (std::cin.eof())
			{
				break;
			}
		}
		else if (str == "SEARCH")
		{
			book_obj.searchContact();
			if (std::cin.eof())
			{
				break;
			}
		}
		else if (str == "EXIT")
		{
			book_obj.showMsg(CBLACK, MSG_EXIT, CRESET);
			break;
		}
		else
		{
			book_obj.showMsg(CRED, WRONG_INPUT, CRESET);
		}
	}
	return (0);
}