/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 12:57:50 by mzolotar          #+#    #+#             */
/*   Updated: 2024/09/17 12:57:52 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	size;
	char	*s_dup;

	size = ft_strlen(s) + 1;
	s_dup = (char *)malloc(size);
	if (!s_dup)
		return (NULL);
	ft_strlcpy(s_dup, s, size);
	return (s_dup);
}
