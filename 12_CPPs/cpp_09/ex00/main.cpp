/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 12:11:04 by mzolotar          #+#    #+#             */
/*   Updated: 2026/02/17 20:19:59 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		showErrorMsg(CRED, "Error: could not open file.", CRESET);
		return (1);
	}
	try
	{
		BitcoinExchange exchange;
		exchange.execute(argv[1]);
	}
	catch (std::exception &e)
	{
		showErrorMsg(CRED, e.what(), CRESET);
		return (1);
	}
	return (0);
}
