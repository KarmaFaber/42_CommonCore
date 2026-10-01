/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdiaz-he <jdiaz-he@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 21:32:18 by isalazar          #+#    #+#             */
/*   Updated: 2025/03/05 10:49:13 by jdiaz-he         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

char	*ft_strchr(char *str, char c)
{
	int	n;

	n = 0;
	while (str[n] != '\0')
	{
		if (str[n] == c)
			return (&str[n]);
		n++;
	}
	if (str[n] == c)
		return (&str[n]);
	return (NULL);
}
