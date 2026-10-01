/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ErrorException.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 14:36:59 by mzolotar          #+#    #+#             */
/*   Updated: 2026/02/02 11:56:00 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_EXCEPTION_HPP
# define ERROR_EXCEPTION_HPP

#include <string>

class ErrorException : public std::exception
{
	private:
		std::string	_message;

	public:
		ErrorException(const std::string& message) throw();
		virtual const char* what() const throw();
		virtual ~ErrorException() throw();
};

#endif