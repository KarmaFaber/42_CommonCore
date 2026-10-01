/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.tpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 10:17:14 by mzolotar          #+#    #+#             */
/*   Updated: 2026/02/17 11:34:39 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

template <typename T>
void	PmergeMe::printContainer(const char* color, const std::string& msg,
						const T& container, const char* reset_color) const
{
	std::cout << color << msg;
	
	typename T::const_iterator it = container.begin();
	
	while (it != container.end())
	{
		std::cout << *it;
		if (++it != container.end())
			std::cout << " ";
	}
	std::cout << reset_color << std::endl;
}
