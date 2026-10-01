/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchrset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdiaz-he <jdiaz-he@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 20:09:08 by jdiaz-he          #+#    #+#             */
/*   Updated: 2025/08/06 15:26:29 by jdiaz-he         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

//Checks if all characters in str are in set.
//Returns 0 if all characters are in set, 1 if not.
//If str[i] is not in set, return 1 (error).
int	ft_strchrset(char *str, char *set)
{
	int	i;

	if (!str || !set)
		return (1);
	i = 0;
	while (str[i])
	{
		if (!ft_strchr(set, str[i]))
			return (i + 1);
		i++;
	}
	return (0);
}
