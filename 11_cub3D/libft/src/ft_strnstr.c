/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isalazar <isalazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 21:37:42 by isalazar          #+#    #+#             */
/*   Updated: 2024/10/01 21:51:53 by isalazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

char	*ft_strnstr(const char *str, const char *find, size_t n)
{
	size_t	o;
	size_t	p;

	o = 0;
	if (!find[0])
		return ((char *)str);
	while (str[o] && o < n)
	{
		p = 0;
		if (str[o] == find[p])
		{
			while ((o + p < n) && str[o + p] == find[p])
			{
				p++;
				if (!find[p])
					return ((char *)&str[o]);
			}
		}
		o++;
	}
	return (0);
}
