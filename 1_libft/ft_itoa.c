/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 10:29:14 by mzolotar          #+#    #+#             */
/*   Updated: 2024/09/30 10:29:19 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief  Returns the number of digits in an integer,
	including the negative sign.
 *
 * @param  n The integer whose digits are to be counted. 
    Handles INT_MIN (32 bits)
 * and LONG_MIN (64 bits) as special cases to avoid overflow.
 *
 * @return The count of digits in the integer,
	including the '-' for negative numbers.
 */

static size_t	ft_count_digits(int number)
{
	int	count;

	count = 0;
	if (number == 0)
		return (1);
	if (number == INT_MIN)
	{
		number = -(number / 10);
		count = 1;
		count++;
	}
	if (number < 0)
	{
		number = -number;
		count++;
	}
	while (number > 0)
	{
		number /= 10;
		count++;
	}
	return (count);
}

/**
 * @brief  Converts an integer to its string representation.
 *
 * @param  n The integer to be converted.
 * @param  new_char A pointer to the allocated memory 
    where the result will be stored.
 * @param  size The size of the string, including the sign and '\0'.
 *
 * @return A pointer to the resulting string.
 */

static void	ft_int_to_char(int n, char *new_char, size_t size)
{
	new_char[size] = '\0';
	if (n == 0)
	{
		new_char[0] = '0';
		return ;
	}
	if (n < 0)
	{
		new_char[0] = '-';
		if (n == INT_MIN)
		{
			new_char[--size] = '8';
			n /= 10;
		}
		n = -n;
	}
	while (n > 0)
	{
		new_char[--size] = (n % 10) + '0';
		n /= 10;
	}
}

/**
 * @brief Converts an integer to a string.
 *
 * @param n The integer to convert.
 *
 * @return Pointer to the string, or NULL if allocation fails.
 */

char	*ft_itoa(int n)
{
	char	*new_char;
	size_t	size;

	size = ft_count_digits(n);
	new_char = (char *)malloc(size + 1);
	if (!new_char)
		return (NULL);
	ft_int_to_char(n, new_char, size);
	return (new_char);
}
