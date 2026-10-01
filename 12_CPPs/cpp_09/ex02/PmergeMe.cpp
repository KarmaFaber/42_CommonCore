/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 09:44:15 by mzolotar          #+#    #+#             */
/*   Updated: 2026/02/17 19:13:12 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

/******************************************************************************/
/*						CONSTRUCTORS & DESTRUCTORS							  */
/******************************************************************************/

PmergeMe::PmergeMe(int inputArgc, char **inputArgv)
				  : _vector_sort_time(0.0),
					_deque_sort_time(0.0)
{
	if (!parseInput(inputArgc, inputArgv))
		throw ErrorException("Error");
	execute();
	outputPrinter();
}

PmergeMe::PmergeMe (PmergeMe const &other)
{
	*this = other;
}

PmergeMe::~PmergeMe() {}

/******************************************************************************/
/*								OPERATORS								  	  */
/******************************************************************************/

PmergeMe&	PmergeMe::operator=(PmergeMe const &other)
{
	if (this != &other)
	{
		this->_my_vector = other._my_vector;
		this->_my_deque = other._my_deque;
		this->_before_data = other._before_data;
		this->_vector_sort_time = other._vector_sort_time;
		this->_deque_sort_time = other._deque_sort_time;
	}
	return (*this);
}

/******************************************************************************/
/*							PRIVATE METHODS									  */
/******************************************************************************/

void	PmergeMe::execute (void)
{
	sortVector();
	sortDeque();
}
