/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copi_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 20:06:26 by mzolotar          #+#    #+#             */
/*   Updated: 2024/11/22 13:28:45 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/**
 * @brief Returns the size of a split string array.
 *
 * @param split The string array to check.
 * @return The size of the array.
 */

int	ft_split_size(char **split)
{
	int	size;

	size = 0;
	if (!split)
		return (0);
	while (split[size])
		size++;
	return (size);
}

/**
 * @brief Allocates memory for a string array of given size.
 *
 * @param size The number of strings to allocate space for.
 * @return The allocated string array.
 */

char	**ft_allocate_copy(int size)
{
	char	**copy;

	copy = (char **)malloc((size + 1) * sizeof(char *));
	if (!copy)
		return (NULL);
	copy[size] = NULL;
	return (copy);
}

/**
 * @brief Creates a copy of a split string array.
 *
 * @param original The original string array to copy.
 * @return A copy of the original string array.
 */

char	**ft_copy_split(char **original)
{
	int		size;
	int		i;
	char	**copy;

	size = ft_split_size(original);
	if (size == 0)
		return (NULL);
	copy = ft_allocate_copy(size);
	if (!copy)
		return (NULL);
	i = 0;
	while (i < size)
	{
		copy[i] = ft_strdup(original[i]);
		if (!copy[i])
		{
			ft_free_split_strs(copy);
			return (NULL);
		}
		i++;
	}
	return (copy);
}
