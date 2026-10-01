/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outputPrinter.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 09:29:06 by mzolotar          #+#    #+#             */
/*   Updated: 2026/02/17 18:51:24 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../PmergeMe.hpp"

/******************************************************************************/
/*							PUBLIC METHODS									  */
/******************************************************************************/

void	PmergeMe::outputPrinter(void) const
{
	showMsg(CMAGENTA, "# ◉─────────▣───▢◇▢───▣───◉•◉───▣───▢ OUTPUT: "
						"▢───▣───◉•◉───▣───▢◇▢───▣─────────◉ #", CRESET);

	printContainer(CCYAN, "Before: ", _before_data, CRESET);

	printContainer(CGREEN, "After:  ", _my_vector, CRESET);

	std::cout << "Time to process a range of " << _my_vector.size() 
			  << " elements with std::vector : " << std::fixed <<
			  (_vector_sort_time * 1000000.0) << " us" << std::endl;

	std::cout << "Time to process a range of " << _my_deque.size() 
			  << " elements with std::deque  : " << std::fixed
			  << (_deque_sort_time * 1000000.0) << " us" << std::endl;

	showMsg(CMAGENTA, "# ◉─────────▣───▢◇▢───▣───◉•◉───▣───▢   END   "
						"▢───▣───◉•◉───▣───▢◇▢───▣─────────◉ #", CRESET);
}
