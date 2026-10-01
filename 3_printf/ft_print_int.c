/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_int.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 09:13:18 by mzolotar          #+#    #+#             */
/*   Updated: 2024/10/14 11:13:42 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_int(int number)
{
	int	digit_count;

	if (number == INT_MIN)
	{
		ft_putnbr_fd(number, 1);
		return (11);
	}
	digit_count = (int)ft_count_digits(number);
	ft_putnbr_fd(number, 1);
	return (digit_count);
}
