/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 08:49:41 by mzolotar          #+#    #+#             */
/*   Updated: 2025/11/06 10:17:24 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKERS_HPP
# define CHECKERS_HPP

#include <string>
#include <cctype>    // isdigit
#include <cstdlib>   // std::strtol
#include <cerrno>    // errno, ERANGE
#include <limits>    // std::numeric_limits

bool	checkSpecial(const std::string& str);
bool	checkChar(const std::string& str);
bool	checkInt(const std::string& str);
bool	checkFloat(const std::string& str, size_t& dot);

#endif
