/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 09:44:12 by mzolotar          #+#    #+#             */
/*   Updated: 2026/02/17 19:13:09 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int	main(int argc, char** argv)
{
	if (argc < 2)
	{
		showError (CRED, "Error", CRESET);
		return (1);
	}
	
	try
	{
		PmergeMe pm(argc,argv);
	}
	catch (std::exception &e)
	{
		showError (CRED, e.what(), CRESET);
		return (1);
	}
	
	return (0);
}