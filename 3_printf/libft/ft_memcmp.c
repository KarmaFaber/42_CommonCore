/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 12:57:19 by mzolotar          #+#    #+#             */
/*   Updated: 2024/09/18 18:16:14 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*s1_pointer;
	const unsigned char	*s2_pointer;
	size_t				i;

	i = 0;
	s1_pointer = (const unsigned char *)s1;
	s2_pointer = (const unsigned char *)s2;
	while (i < n)
	{
		if (s1_pointer[i] != s2_pointer[i])
			return (s1_pointer[i] - s2_pointer[i]);
		i++;
	}
	return (0);
}
