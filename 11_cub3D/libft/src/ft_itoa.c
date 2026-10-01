/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdiaz-he <jdiaz-he@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 18:46:01 by jdiaz-he          #+#    #+#             */
/*   Updated: 2025/02/11 11:56:59 by jdiaz-he         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

static int	ft_nbrdigc(long n)
{
	int	size;

	size = 1;
	if (n < 0)
	{
		size++;
		n *= -1;
	}
	while (n > 9)
	{
		n /= 10;
		size++;
	}
	return (size);
}

static int	ft_minint(char *str)
{
	str[0] = '-';
	str[1] = '2';
	return (147483648);
}

char	*ft_itoa(int n)
{
	char	*nitoa;
	int		size;

	size = ft_nbrdigc(n);
	nitoa = malloc((size + 1) * sizeof(char));
	if (!nitoa)
		return (0);
	nitoa[size] = 0;
	if (n == -2147483648)
		n = ft_minint(nitoa);
	else if (n < 0)
	{
		nitoa[0] = '-';
		n = -n;
	}
	if (n == 0)
		nitoa[0] = '0';
	while (n > 0)
	{
		nitoa[--size] = n % 10 + 48;
		n /= 10;
	}
	return (nitoa);
}
