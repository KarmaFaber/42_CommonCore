/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 12:07:39 by mzolotar          #+#    #+#             */
/*   Updated: 2024/11/27 10:39:23 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/**
 * @brief Opens the map file and returns its file descriptor.
 *
 * @param vars Pointer to the game variables structure.
 * @return int File descriptor of the opened file.
 */
int	open_map_file(t_vars *vars)
{
	int	fd;

	fd = open(vars->map_path, O_RDONLY);
	if (fd == -1)
	{
		ft_error(vars, "\033[1;31m🛑ERROR:\nError opening map file.\033[0m\n");
	}
	return (fd);
}

/**
 * @brief Allocates memory for the map string.
 *
 * @param size Size of the map.
 * @param vars Pointer to the game variables structure.
 * @return char* Pointer to the allocated map string.
 */
char	*allocate_map_memory(size_t size, t_vars *vars)
{
	char	*str_map;

	if (size == 0)
	{
		ft_error(vars, "\033[1;31m🛑ERROR:\nMap is empty.\033[0m\n");
	}
	str_map = (char *)ft_calloc(size + 1, sizeof(char));
	if (!str_map)
	{
		ft_error(vars,
			"\033[1;31m🛑ERROR:\nAllocation failed for str_map.\033[0m\n");
	}
	return (str_map);
}

/**
 * @brief Verifies that the map string is not empty after reading.
 *
 * @param str_map Pointer to the map string.
 * @param vars Pointer to the game variables structure.
 */
void	verify_map_not_empty(char *str_map, t_vars *vars)
{
	if (ft_strlen(str_map) == 0)
	{
		free(str_map);
		ft_error(vars, "\033[1;31m🛑ERROR:\nMap is empty.\033[0m\n");
	}
}
