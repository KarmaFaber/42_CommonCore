/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 12:38:26 by mzolotar          #+#    #+#             */
/*   Updated: 2024/11/27 10:37:04 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/**
 * @brief Checks if the map is rectangular by comparing row lengths.
 *
 * @param split_strs The split map rows.
 * @param vars The game variables.
 * @return void
 */

void	check_is_rectangular(char **split_strs, t_vars *vars)
{
	size_t	expected_length;
	size_t	i;

	if (!split_strs || !split_strs[0])
		ft_error(vars, "\033[1;31m🛑ERROR:\nMap is empty or invalid.\033[0m\n");
	expected_length = ft_strlen(split_strs[0]);
	i = 1;
	while (split_strs[i])
	{
		if (ft_strlen(split_strs[i]) != expected_length)
			ft_error(vars, "\033[1;31m🛑ERROR:\nMap is not rectang.\033[0m\n");
		i++;
	}
}

/**
 * @brief Verifies that the first row of the map is surrounded by walls.
 *
 * @param first_row The first row of the map.
 * @param vars The game variables.
 * @return void
 */

static void	check_first_row_walls(char *first_row, t_vars *vars)
{
	size_t	i;

	if (!first_row)
		ft_error(vars, "\033[1;31m🛑ERROR:\nFirst row is invalid.\033[0m\n");
	i = 0;
	while (first_row[i])
	{
		if (first_row[i] != '1')
			ft_error(vars,
				"\033[1;31m🛑ERROR:\nFirst row not sur. by walls.\033[0m\n");
		i++;
	}
}

/**
 * @brief Verifies that the last row of the map is surrounded by walls.
 *
 * @param last_row The last row of the map.
 * @param vars The game variables.
 * @return void
 */

static void	check_last_row_walls(char *last_row, t_vars *vars)
{
	size_t	i;

	if (!last_row)
		ft_error(vars, "\033[1;31m🛑ERROR:\nLast row is invalid.\033[0m\n");
	i = 0;
	while (last_row[i])
	{
		if (last_row[i] != '1')
			ft_error(vars,
				"\033[1;31m🛑ERROR:\nLast row not sur. by walls.\033[0m\n");
		i++;
	}
}

/**
 * @brief Verifies that the first and last rows are valid map walls.
 *
 * @param split_strs The split map rows.
 * @param vars The game variables.
 * @return void
 */

void	check_first_and_last_row_walls(char **split_strs, t_vars *vars)
{
	size_t	last_row_index;

	if (!split_strs || !split_strs[0])
		ft_error(vars, "\033[1;31m🛑ERROR:\nMap is empty or invalid.\033[0m\n");
	last_row_index = 0;
	while (split_strs[last_row_index] != NULL)
		last_row_index++;
	if (last_row_index == 0)
		ft_error(vars,
			"\033[1;31m🛑ERROR:\nMap content is insufficient.\033[0m\n");
	check_first_row_walls(split_strs[0], vars);
	check_last_row_walls(split_strs[last_row_index - 1], vars);
}

/**
 * @brief Verifies that intermediate rows are surrounded by walls.
 *
 * @param split_strs The split map rows.
 * @param vars The game variables.
 * @return void
 */

void	check_intermediate_row_walls(char **split_strs, t_vars *vars)
{
	size_t	len;
	size_t	i;

	i = 1;
	while (split_strs[i] != NULL && split_strs[i + 1] != NULL)
	{
		len = ft_strlen(split_strs[i]);
		if (split_strs[i][0] != '1' || split_strs[i][len - 1] != '1')
		{
			ft_error(vars,
				"\033[1;31m🛑ERROR:\nMap isn't surr.: intermed. row.\033[0m\n");
		}
		i++;
	}
}
