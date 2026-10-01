/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isalazar <isalazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 10:11:27 by jdiaz-he          #+#    #+#             */
/*   Updated: 2024/07/26 20:09:40 by isalazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	count;
	int		r;

	r = 0;
	count = 0;
	while ((s1[count] != 0 || s2[count] != 0))
	{
		r = (unsigned char) s1[count] - (unsigned char) s2[count];
		if (r != 0)
			break ;
		count++;
	}
	return (r);
}
