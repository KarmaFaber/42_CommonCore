/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 08:15:33 by mzolotar          #+#    #+#             */
/*   Updated: 2026/02/17 19:25:37 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <cstdlib>
#include <stack>

#include "utils/ErrorException.hpp"
#include "utils/Utils.hpp"

class RPN
{
	private:
		std::stack<double>	_my_stack;

		bool	syntaxParser(const std::string& inputStr);
		bool	isValidChar(char c);
		bool	isValidOperator(char c);

	public:
		RPN(char const *inputArgv);
		RPN(RPN const &other);
		RPN& operator=(RPN const &other);
		~RPN();
		
		int		getResult(void) const;
		void	runCalculator(const std::string& inputStr);
		double	calculate(double firstNum, double secondNum, char oper);
};

#endif