/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printdec_unsig.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 09:13:39 by mzolotar          #+#    #+#             */
/*   Updated: 2024/09/20 12:12:19 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printdec_unsig(unsigned int number)
{
	int	digit_count;

	digit_count = ft_count_digits_unsigned(number);
	ft_putnbr_unsigned_fd(number, 1);
	return (digit_count);
}
