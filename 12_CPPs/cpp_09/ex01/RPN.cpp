/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 08:15:26 by mzolotar          #+#    #+#             */
/*   Updated: 2026/02/17 19:22:42 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

/******************************************************************************/
/*						CONSTRUCTORS & DESTRUCTORS							  */
/******************************************************************************/
RPN::RPN (char const *inputArgv)
{
	if (!syntaxParser(inputArgv))
		throw (ErrorException("Error"));
	runCalculator(inputArgv);
}

RPN::RPN (RPN const &other)
{
	*this = other;
}

RPN::~RPN() {}

/******************************************************************************/
/*								OPERATORS								  	  */
/******************************************************************************/
RPN&	RPN::operator=(RPN const &other)
{
	if (this != &other)
	{
		this->_my_stack = other._my_stack;
	}
	return (*this);
}

/******************************************************************************/
/*								GETTERS										  */
/******************************************************************************/
int	RPN::getResult(void) const
{
	return (static_cast<int>(_my_stack.top()));
}

/******************************************************************************/
/*							PUBLIC METHODS									  */
/******************************************************************************/
void	RPN::runCalculator(const std::string& inputStr)
{
	size_t	i = 0;

	while (i < inputStr.length())
	{
		if (std::isspace(inputStr[i]))
		{
			i++;
			continue;
		}
		if (std::isdigit(inputStr[i]))
			_my_stack.push(inputStr[i] - '0');
		else if (isValidOperator(inputStr[i]))
		{
			if (_my_stack.size() < 2)
				throw ErrorException("Error");
			double	second = _my_stack.top();
			_my_stack.pop();
			double	first = _my_stack.top();
			_my_stack.pop();
			_my_stack.push(calculate(first, second, inputStr[i]));
		}
		i++;
	}
	if (_my_stack.size() != 1)
		throw ErrorException("Error");
}


double	RPN::calculate(double firstNum, double secondNum, char oper)
{
	if (oper == '+')
		return (firstNum + secondNum);
	if (oper == '-')
		return (firstNum - secondNum);
	if (oper == '*')
		return (firstNum * secondNum);
	if (oper == '/')
	{
		if (secondNum == 0)
			throw ErrorException("Error: Division by zero.");
		return (firstNum / secondNum);
	}
	return (0);
	
}
