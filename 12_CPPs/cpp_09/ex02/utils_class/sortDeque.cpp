/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sortDeque.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 09:21:51 by mzolotar          #+#    #+#             */
/*   Updated: 2026/02/17 18:53:42 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../PmergeMe.hpp"

/******************************************************************************/
/*							PRIVATE METHODS									  */
/******************************************************************************/

void	PmergeMe::sortDeque(void)
{
	struct timeval start, end;

	gettimeofday(&start, NULL);
	_my_deque.assign(_before_data.begin(), _before_data.end());

	if (_my_deque.size() < 2)
	{
		gettimeofday(&end, NULL);
		_deque_sort_time = (end.tv_sec - start.tv_sec) + 
							(static_cast<double>(end.tv_usec - start.tv_usec) / 1000000.0);
		return;
	}
	fordJohnsonDeque(_my_deque);
	gettimeofday(&end, NULL);
	_deque_sort_time = (end.tv_sec - start.tv_sec) + 
							(static_cast<double>(end.tv_usec - start.tv_usec) / 1000000.0);
}

void	PmergeMe::fordJohnsonDeque(std::deque<int>& our_deque)
{
	if (our_deque.size() < 2)
		return;
		
	std::deque< std::pair<int, int> >	pairs;
	bool	hasStraggler = false;
	int		straggler = -1;
	
	pairs = buildPairsDeque(our_deque, hasStraggler, straggler);
	
	std::deque<int> largerElements;
	for (size_t i = 0; i < pairs.size(); ++i)
		largerElements.push_back(pairs[i].first);

	fordJohnsonDeque(largerElements);

	our_deque.clear();
	our_deque = largerElements;
	std::deque<int> pend = builtPendDeque(our_deque, pairs);
	
	our_deque.push_front(pend[0]); 
	std::deque<int> jacob = generateJacobsthalDeque(pend.size());
	insertPendToMainChainDeque(our_deque, pend, jacob);
	
	if (hasStraggler)
	{
		std::deque<int>::iterator it = std::lower_bound(our_deque.begin(),our_deque.end(), straggler);
		our_deque.insert(it, straggler);
	}
}

std::deque< std::pair<int, int> >	PmergeMe::buildPairsDeque(std::deque<int>& our_deque, bool &hasStraggler, int& straggler)
{
	std::deque< std::pair<int, int> > pairs;
	
	if (our_deque.size() % 2 != 0)
	{
		straggler = our_deque.back();
		our_deque.pop_back();
		hasStraggler = true;
	}

	for (size_t i = 0; i < our_deque.size(); i += 2)
	{
		int n1 = our_deque[i];
		int n2 = our_deque[i + 1];
		if (n1 > n2)
			pairs.push_back(std::make_pair(n1, n2));
		else
			pairs.push_back(std::make_pair(n2, n1));
	}
	return (pairs);
}

std::deque<int>	PmergeMe::builtPendDeque(std::deque<int>& our_deque, std::deque< std::pair<int, int> >& pairs)
{
	std::deque<int> pend;
	
	for (size_t i = 0; i < our_deque.size(); ++i)
	{
		for (size_t j = 0; j < pairs.size(); ++j)
		{
			if (our_deque[i] == pairs[j].first)
			{
				pend.push_back(pairs[j].second);
				break;
			}
		}
	}
	return (pend);
}

std::deque<int>	PmergeMe::generateJacobsthalDeque(size_t n)
{
	std::deque<int> jacob;
	if (n == 0)
		return (jacob);

	jacob.push_back(1);
	jacob.push_back(3);
		
	while (jacob.back() < static_cast<int>(n))
	{
		int next = jacob[jacob.size() - 1] + 2 * jacob[jacob.size() - 2];
		jacob.push_back(next);
	}
	return (jacob);
}

void	PmergeMe::insertPendToMainChainDeque(std::deque<int>& our_deque, std::deque<int>& pend, std::deque<int>& jacob)
{
	size_t last_pos = 1;

	for (size_t i = 1; i < jacob.size(); ++i)
	{
		size_t curr_pos = jacob[i];
		if (curr_pos > pend.size())
			curr_pos = pend.size();

		for (size_t j = curr_pos; j > last_pos; --j)
		{
			int val = pend[j - 1];
			
			std::deque<int>::iterator it = std::lower_bound(our_deque.begin(), our_deque.end(), val);
			
			our_deque.insert(it, val);
		}
		last_pos = curr_pos;
	}
}
