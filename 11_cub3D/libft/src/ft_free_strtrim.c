/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_strtrim.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdiaz-he <jdiaz-he@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 13:44:48 by jdiaz-he          #+#    #+#             */
/*   Updated: 2025/02/11 14:00:58 by jdiaz-he         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

/*
Used for freeing a string with a callback function
in this case used with ft_strtrim(char *str, char *set)
*/
char	*ft_free_strtrim(
	char *to_free, char *str, char *(*f)(const char *, const char *))
{
	char	*r;

	r = f(to_free, str);
	if (!r)
		return (to_free);
	free(to_free);
	return (r);
}
