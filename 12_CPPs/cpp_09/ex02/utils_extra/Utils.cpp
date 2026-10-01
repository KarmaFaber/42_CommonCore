/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 07:59:42 by mzolotar          #+#    #+#             */
/*   Updated: 2026/02/06 07:38:25 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Utils.hpp"

/******************************************************************************/
/*                            Utils FUNCTION                                  */
/******************************************************************************/
void	showError(const char* color, const char* msg, const char* reset)
{
	std::cerr << color << msg << reset << std::endl;
}

void	showMsg(const char* color, const char* msg, const char* reset)
{
	std::cout << color << msg << reset << std::endl;
}
