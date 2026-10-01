/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 10:33:51 by mzolotar          #+#    #+#             */
/*   Updated: 2025/11/10 11:17:58 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Span.hpp"

/******************************************************************************/
/*						CONSTRUCTORS & DESTRUCTORS							  */
/******************************************************************************/
/*	Default Constructor		*/
Span::Span()
		:	_N(0) {}

/*	Atribute Constructor	*/
Span::Span(unsigned int N)
		:	_N(N) {}

/*	Copy Constructor		*/
Span::Span(const Span &other)
{
	*this = other;
}

/*	Desctructor				*/
Span::~Span() {}

/******************************************************************************/
/*								OPERATORS								  	  */
/******************************************************************************/
/*	Copy Assignment Operator	*/
Span& Span::operator=(const Span &other)
{
	if (this != &other) {
		this->_N = other._N;
		this->_data = other._data;
	}
	return (*this);
}

/******************************************************************************/
/*								EXCEPTIONS									  */
/******************************************************************************/

const char	*Span::FullSpanException::what() const throw()
{
	return ("Span is full");
}

const char	*Span::NotEnoughNumbersException::what() const throw()
{
	return ("Not enough numbers to find a span");
}


/******************************************************************************/
/*							PUBLIC METHODS									  */
/******************************************************************************/

void	Span::addNumber(int num)
{
	if (_data.size() >= _N)
		throw (FullSpanException());
	_data.push_back(num);
}

unsigned int	Span::shortestSpan() const
{
	if (_data.size() < 2)
		throw (NotEnoughNumbersException());

	std::vector<int> sorted = _data;
	std::sort(sorted.begin(), sorted.end());

	unsigned int minSpan = sorted[1] - sorted[0];
	for (size_t i = 1; i < sorted.size() - 1; ++i) {
		unsigned int span = sorted[i + 1] - sorted[i];
		if (span < minSpan)
			minSpan = span;
	}
	return (minSpan);
}

unsigned int	Span::longestSpan() const
{
	if (_data.size() < 2)
		throw (NotEnoughNumbersException());

	unsigned int minVal = *std::min_element(_data.begin(), _data.end());
	unsigned int maxVal = *std::max_element(_data.begin(), _data.end());
	return (maxVal - minVal);
}
