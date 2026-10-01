/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ErrorException.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 14:37:19 by mzolotar          #+#    #+#             */
/*   Updated: 2026/02/04 08:08:53 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ErrorException.hpp"

ErrorException::ErrorException(const std::string& message) throw()
	: _message("Error: " + message) {}

const char* ErrorException::what() const throw()
{
	return (_message.c_str());
}

ErrorException::~ErrorException() throw() {}
