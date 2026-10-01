/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 10:34:14 by mzolotar          #+#    #+#             */
/*   Updated: 2025/11/10 11:17:08 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPAN_HPP
#define SPAN_HPP

#include <iostream>
#include <vector>
#include <algorithm>
#include <exception>
//#include <cstdlib>

class Span 
{
	private:
		unsigned int		_N;
		std::vector<int>	_data;

	public:
		Span();
		Span(unsigned int num);
		Span(const Span &other);
		Span &operator=(const Span &other);
		~Span();

		//methods
		void				addNumber(int num);
		
		template<typename It>
		void addNumber(It begin, It end)
		{
			if (_data.size() + std::distance(begin, end) > _N)
				throw std::runtime_error("Adding range exceeds Span capacity");
			_data.insert(_data.end(), begin, end);
		}

		unsigned int		shortestSpan() const;		//Returns the minimum difference between two numbers.
		unsigned int		longestSpan() const;		//Returns the maximum difference between two numbers

		//exceptions
		class FullSpanException : public std::exception
		{
			public:
				virtual const char *what() const throw();
		};

		class NotEnoughNumbersException : public std::exception
		{
			public:
				virtual const char *what() const throw();
		};
	};

#endif
