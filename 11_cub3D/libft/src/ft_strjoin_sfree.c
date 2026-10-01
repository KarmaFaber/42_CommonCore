/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_sfree.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdiaz-he <jdiaz-he@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 11:01:35 by jdiaz-he          #+#    #+#             */
/*   Updated: 2025/06/06 19:15:51 by jdiaz-he         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

//strjoin with selective free, you can pass both strings to free or 
//NULL to not free a string
//or pass another string to free it
char	*ft_strjoin_sfree(char *s1, char *s2, char *for_free1, char *for_free2)
{
	char	*tmp;

	tmp = ft_strjoin(s1, s2);
	if (for_free1)
	{
		free(for_free1);
		for_free1 = NULL;
	}
	if (for_free2)
	{
		free(for_free2);
		for_free2 = NULL;
	}
	return (tmp);
}
