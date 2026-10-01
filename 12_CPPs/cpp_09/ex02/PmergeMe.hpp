/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 09:44:19 by mzolotar          #+#    #+#             */
/*   Updated: 2026/02/17 19:08:15 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <string>
#include <sstream>
#include <climits>
#include <cstdlib>

#include <sys/time.h>

#include <deque>
#include <vector>
#include <set>

#include "utils_extra/ErrorException.hpp"
#include "utils_extra/Utils.hpp"


class PmergeMe
{
	private:
		std::vector<int>	_before_data;

		std::vector<int>	_my_vector;
		std::deque<int>		_my_deque;

		double				_vector_sort_time;
		double				_deque_sort_time;

		//parserInput.cpp
			bool	parseInput(int argc, char **argv);
			bool	hasSyntaxError(std::string str_token);
			bool	hasLogicError(long long_token);
			bool	isRepetedValue(std::vector<int> &before_data);
			long	convertLong(std::string str_token);
		//sortVector.cpp
			void	sortVector(void);
			void	fordJohnsonVector(std::vector<int>& our_vector);
			std::vector< std::pair<int, int> >	buildPairsVector(std::vector<int>& our_vector,bool &hasStraggler, int& straggler );
			std::vector<int>					builtPendVector(std::vector<int>& our_vector, std::vector< std::pair<int, int> >& pairs);
			std::vector<int>					generateJacobsthalVector(size_t n);
			void								insertPendToMainChainVector(std::vector<int>& our_vector, std::vector<int>& pend, std::vector<int>& jacob);
		//sortDeque.cpp
			void	sortDeque(void);
			void	fordJohnsonDeque(std::deque<int>& our_deque);
			std::deque< std::pair<int, int> >	buildPairsDeque(std::deque<int>& our_deque, bool &hasStraggler, int& straggler);
			std::deque<int>						builtPendDeque(std::deque<int>& our_deque, std::deque< std::pair<int, int> >& pairs);
			std::deque<int>						generateJacobsthalDeque(size_t n);
			void								insertPendToMainChainDeque(std::deque<int>& our_deque, std::deque<int>& pend, std::deque<int>& jacob);
		//PmergeMe.cpp
			void	execute (void);
		// --- TEMPLATES --->> PmergeMe.tpp
			template <typename T>
			void	printContainer(const char* color, const std::string& msg, const T& container, const char* reset_color) const;

	public:
		PmergeMe(int inputArgc, char **inputArgv);
		PmergeMe(PmergeMe const &other);
		PmergeMe& operator=(PmergeMe const &other);
		~PmergeMe();

		void	outputPrinter(void) const;
};

#include "PmergeMe.tpp"

#endif