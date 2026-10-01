/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdiaz-he <jdiaz-he@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 17:28:14 by jdiaz-he          #+#    #+#             */
/*   Updated: 2024/03/25 17:07:15 by jdiaz-he         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

void	ft_putnbr(int n)
{
	char	c;

	if (n == -2147483648)
		ft_write(1, "-2147483648", 11);
	else if (n < 0)
	{
		ft_write(1, "-", 1);
		ft_putnbr(n * -1);
	}
	else if (n < 10)
	{
		c = n + 48;
		ft_write(1, &c, 1);
	}
	else
	{
		ft_putnbr(n / 10);
		ft_putnbr(n % 10);
	}
}
