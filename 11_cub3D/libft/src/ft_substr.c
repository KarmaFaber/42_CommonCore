/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdiaz-he <jdiaz-he@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 04:13:15 by jdiaz-he          #+#    #+#             */
/*   Updated: 2024/10/01 02:05:25 by jdiaz-he         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char				*sub;
	char				*r_sub;
	unsigned int		i;

	if (!s)
		return (0);
	if (start > ft_strlen(s))
		len = 0;
	else if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	sub = ft_calloc((len + 1), sizeof(char));
	if (!sub)
		return (0);
	r_sub = sub;
	i = 0;
	if (start < ft_strlen(s))
		while (s[start + i] && len--)
			*sub++ = s[start + i++];
	*sub = 0;
	return (r_sub);
}
