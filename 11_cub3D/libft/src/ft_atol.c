/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdiaz-he <jdiaz-he@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 18:34:00 by jdiaz-he          #+#    #+#             */
/*   Updated: 2024/06/23 20:33:36 by jdiaz-he         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

/**
*	Convierte la parte inicial del string apuntado
*	por str a long int.
*	
*	@param	str : Puntero a la cadena de caracteres.
*	@return	Cadena de caracteres convertida a long int o 0 si error.
*/
long int	ft_atol(const char *str)
{
	long int	n;
	int			sign;

	n = 0;
	sign = 1;
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	if (*str == 43 || *str == 45)
	{
		if (*str == 45)
			sign *= -1;
		str++;
	}
	while (*str && ft_isdigit(*str) != 0)
	{
		n *= 10;
		n += *str - 48;
		str++;
	}
	return (n * sign);
}
