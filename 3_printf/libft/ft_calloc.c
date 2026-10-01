/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 12:50:25 by mzolotar          #+#    #+#             */
/*   Updated: 2024/09/18 18:08:57 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*pointer;
	size_t	total_mem;

	total_mem = nmemb * size;
	pointer = malloc(total_mem);
	if (!pointer)
		return (NULL);
	ft_bzero(pointer, total_mem);
	return (pointer);
}
