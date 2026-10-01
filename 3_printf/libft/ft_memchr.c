/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 12:57:16 by mzolotar          #+#    #+#             */
/*   Updated: 2024/09/18 18:14:44 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*s_pointer;
	size_t				i;

	s_pointer = (const unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (s_pointer[i] == (unsigned char)c)
			return ((void *)&s_pointer[i]);
		i++;
	}
	return (NULL);
}
