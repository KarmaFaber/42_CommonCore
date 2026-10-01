/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sortVector.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 09:22:22 by mzolotar          #+#    #+#             */
/*   Updated: 2026/02/17 19:16:49 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../PmergeMe.hpp"

/******************************************************************************/
/*							PRIVATE METHODS									  */
/******************************************************************************/

void	PmergeMe::sortVector(void)
{
	struct timeval start, end;

	gettimeofday(&start, NULL);
	_my_vector.assign(_before_data.begin(), _before_data.end());

	if (_my_vector.size() < 2)
	{
		gettimeofday(&end, NULL);
		_vector_sort_time = (end.tv_sec - start.tv_sec) + 
							(static_cast<double>(end.tv_usec - start.tv_usec) / 1000000.0);
		return;
	}
	fordJohnsonVector(_my_vector);
	gettimeofday(&end, NULL);

	_vector_sort_time = (end.tv_sec - start.tv_sec) + 
						(static_cast<double>(end.tv_usec - start.tv_usec) / 1000000.0);
}

void	PmergeMe::fordJohnsonVector(std::vector<int>& our_vector)
{
	if (our_vector.size() < 2)
		return;
		
	std::vector< std::pair<int, int> >	pairs;
	bool	hasStraggler = false;
	int		straggler = -1;
	
	pairs = buildPairsVector (our_vector, hasStraggler, straggler);
	
	std::vector<int> largerElements;
	for (size_t i = 0; i < pairs.size(); ++i)
		largerElements.push_back(pairs[i].first);

	fordJohnsonVector(largerElements);

	our_vector.clear();
	our_vector = largerElements;
	std::vector<int> pend = builtPendVector(our_vector, pairs);
	
	our_vector.insert(our_vector.begin(), pend[0]);
	std::vector<int> jacob = generateJacobsthalVector(pend.size());
	insertPendToMainChainVector(our_vector, pend, jacob);
	
	if (hasStraggler)
	{
		std::vector<int>::iterator it = std::lower_bound(our_vector.begin(), our_vector.end(), straggler);
		our_vector.insert(it, straggler);
	}
}

std::vector< std::pair<int, int> >	PmergeMe::buildPairsVector(std::vector<int>& our_vector,bool &hasStraggler, int& straggler)
{
	std::vector< std::pair<int, int> > pairs;
	
	if (our_vector.size() % 2 != 0)
	{
		straggler = our_vector.back();
		our_vector.pop_back();
		hasStraggler = true;
	}

	for (size_t i = 0; i < our_vector.size(); i += 2)
	{
		int n1 = our_vector[i];
		int n2 = our_vector[i + 1];
		if (n1 > n2)
			pairs.push_back(std::make_pair(n1, n2));
		else
			pairs.push_back(std::make_pair(n2, n1));
	}
	return (pairs);
}

std::vector<int>	PmergeMe::builtPendVector(std::vector<int>& our_vector, std::vector< std::pair<int, int> >& pairs)
{
	std::vector<int> pend;
	
	for (size_t i = 0; i < our_vector.size(); ++i)
	{
		for (size_t j = 0; j < pairs.size(); ++j)
		{
			if (our_vector[i] == pairs[j].first)
			{
				pend.push_back(pairs[j].second);
				break;
			}
		}
	}
	return (pend);
}

std::vector<int>	PmergeMe::generateJacobsthalVector(size_t n)
{
	std::vector<int> jacob;
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

void	PmergeMe::insertPendToMainChainVector(std::vector<int>& our_vector, std::vector<int>& pend, std::vector<int>& jacob)
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
			
			std::vector<int>::iterator it = std::lower_bound(our_vector.begin(), our_vector.end(), val);
			
			our_vector.insert(it, val);
		}
		last_pos = curr_pos;
	}
}
