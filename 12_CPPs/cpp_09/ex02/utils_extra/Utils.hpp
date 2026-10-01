/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 08:35:52 by mzolotar          #+#    #+#             */
/*   Updated: 2026/02/06 07:38:42 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
# define UTILS_HPP

/* Colors */
#define CRED				"\033[0;31m"
#define CBLACK				"\033[0;30m"
#define CBLUE				"\033[0;34m"
#define CGREEN				"\033[0;32m"
#define CYELLOW				"\033[0;33m"
#define CMAGENTA			"\033[0;35m"
#define CCYAN				"\e[36m"
#define BG_BRIGHT_CYAN		"\e[106m"
#define BG_BRIGHT_YELLOW	"\e[103m"
#define CRESET				"\033[0m"

#include <string>
#include <iostream>

/* Utils.cpp */
void	showError(const char* color, const char* msg, const char* reset);
void	showMsg(const char* color, const char* msg, const char* reset);

#endif