/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdiaz-he <jdiaz-he@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 02:17:10 by jdiaz-he          #+#    #+#             */
/*   Updated: 2025/06/02 22:40:28 by jdiaz-he         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

char	*ft_strdup(const char *s)
{
	char	*s_mem;
	char	*s_mem_r;

	s_mem = (char *) ft_calloc((ft_strlen(s) + 1), sizeof(char));
	s_mem_r = s_mem;
	if (!s_mem)
		return (NULL);
	while (*s)
		*s_mem++ = *s++;
	*s_mem = '\0';
	return (s_mem_r);
}
