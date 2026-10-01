/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 09:55:39 by mzolotar          #+#    #+#             */
/*   Updated: 2025/05/13 12:20:13 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Checks if a string contains only numeric digits.
 *
 * @param str String to check.
 * @return true if all characters are digits, false otherwise.
 */

static bool	contain_digits_only(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

/**
 * @brief Converts a digit-only string into a positive integer.
 *
 * @param sptr: sring to convert
 * @return Returns the converted number between 0 and INT MAX.
 * @return	Returns -1 if the converted number exceeds INT MAX.
 */

int	atol_unsigned(const char *nptr)
{
	unsigned long int	number;
	int					i;

	i = 0;
	number = 0;
	while (nptr[i] && (nptr[i] >= '0' && nptr[i] <= '9'))
	{
		number = number * 10 + (nptr[i] - '0');
		i++;
	}
	if (number > INT_MAX)
		return (-1);
	return ((int)number);
}

/**
 * @brief Validates command-line arguments for correct format and range.
 *
 * @param argc_var Argument count.
 * @param argv_var Array of argument strings.
 * @return true if all arguments are valid, false otherwise.
 */

bool	check_argvs(int argc_var, char **argv_var)
{
	int	i;
	int	number;

	i = 1;
	if (argc_var - 1 < 4 || argc_var - 1 > 5)
		return (printf("%s", STR_ERR_ARG), 0);
	while (i < argc_var)
	{
		if (!contain_digits_only(argv_var[i]))
			return (printf("%s", STR_ERR_INPUT_DIGIT), 0);
		number = atol_unsigned(argv_var[i]);
		if (i == 1 && (number <= 0 || number > MAX_PHILOS))
			return (printf("%s", STR_ERR_P_NUM), 0);
		if (i != 1 && number == -1)
			return (printf("%s", STR_ERR_INPUT_DIGIT), 0);
		i++;
	}
	return (1);
}
