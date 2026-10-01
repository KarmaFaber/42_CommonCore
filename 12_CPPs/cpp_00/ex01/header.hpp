/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 20:45:45 by mzolotar          #+#    #+#             */
/*   Updated: 2025/09/22 20:58:47 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_HPP
# define HEADER_HPP

# define MAX_LEN		10
# define MAX_ID			8
# define MAX_NUM_LEN	15
# define MAX_ATTEMPTS	3

# define CRED			"\033[0;31m"
# define CBLACK			"\033[0;30m"
# define CBLUE			"\033[0;34m"
# define CGREEN			"\033[0;32m"
# define CRESET			"\033[0m"

//main:
# define MSG_EXIT		"See you soon!"
# define WRONG_INPUT	"Invalid command. Please enter ADD, SEARCH or EXIT."
# define INSTRUCTIONS	"Enter your command: ADD, SEARCH or EXIT"

//phoneBook methods:
# define MSG_EOF		"Input terminated (EOF). Exiting."
# define MSG_BAD_INPUT	"Too many invalid attempts. Exiting."
# define MSG_QUIT		"Quit searching"
# define MSG_EMPTY		"The phonebook is empty. Please add a contact first."
# define MSG_FULL		"The phonebook is full. The oldest contact will be replaced."
# define MSG_SAVE		"Contact saved successfully!"
# define MSG_INSTRUCT	"Enter the index of the contact you want to view(0 to quit searching)."
# define INVALID_INPUT	"Invalid input. Please enter a valid value."
# define INVALID_INDEX	"Invalid index. Please enter a number between 1 and 8."
# define INVALID_CONT	"This contact does not exist. Please enter a valid index."

# define INVALID_FNAME	"Invalid first name. Please use only letters, spaces, hyphens and apostrophes."
# define INVALID_NAME	"Invalid name. Please use only letters, spaces, hyphens and apostrophes."
# define INVALID_NICKNAME	"Invalid nickname. Please use only letters, numbers, underscores and hyphens."
# define INVALID_NUMBER	"Invalid phone number. Please enter only digits."
# define INVALID_SECRET	"Invalid secret. Please avoid control characters."

//table
# define TABLE_START		" ˍˍˍˍˍˍˍˍˍˍˍˍˍˍˍˍˍˍˍˍˍˍˍˍˍˍˍˍˍˍˍˍˍˍˍˍˍˍˍˍˍˍˍ "
# define TABLE_INDEX		"║     Index|First Name| Last Name|  Nickname║"
# define TABLE_MID			"║----------|----------|----------|----------║"
# define TABLE_END			" ˉˉˉˉˉˉˉˉˉˉˉˉˉˉˉˉˉˉˉˉˉˉˉˉˉˉˉˉˉˉˉˉˉˉˉˉˉˉˉˉˉˉˉ "

#endif