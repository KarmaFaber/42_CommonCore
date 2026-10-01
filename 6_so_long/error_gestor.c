/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_gestor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 20:48:05 by mzolotar          #+#    #+#             */
/*   Updated: 2024/11/27 10:38:22 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/**
 * @brief Frees all memory associated with the map data structure.
 *
 * @param map_data Pointer to the map data structure.
 * @return void
 */

void	ft_free_map_data(t_map_data *map_data)
{
	if (!map_data)
		return ;
	if (map_data->str_map)
	{
		free(map_data->str_map);
		map_data->str_map = NULL;
	}
	if (map_data->split_strs)
	{
		ft_free_split_strs(map_data->split_strs);
		map_data->split_strs = NULL;
	}
	if (map_data->map_copy)
	{
		ft_free_split_strs(map_data->map_copy);
		map_data->map_copy = NULL;
	}
}

/**
 * @brief Frees memory allocated for the map string.
 *
 * @param str_map Pointer to the map string to free.
 * @return void
 */

void	ft_free_str_map(char *str_map)
{
	if (str_map)
		free(str_map);
}

/**
 * @brief Frees memory for an array of strings and its content.
 *
 * @param split_strs Pointer to the array of strings to free.
 * @return void
 */

void	ft_free_split_strs(char **split_strs)
{
	int	i;

	if (!split_strs)
		return ;
	i = 0;
	while (split_strs[i])
	{
		free(split_strs[i]);
		split_strs[i] = NULL;
		i++;
	}
	free(split_strs);
	split_strs = NULL;
}

/**
 * @brief Displays an error message and exits the program.
 *
 * @param vars Pointer to the game variables structure.
 * @param err Error message to display.
 * @return void
 */

void	ft_error(t_vars *vars, char *err)
{
	ft_printf("\033[1;31m %s \033[0m\n", err);
	handle_exit(vars);
	exit(1);
}

/**
 * @brief Generates an error message if required map elements are missing.
 *
 * @param vars Pointer to the game variables structure.
 * @return char* Error message string, or NULL if no error.
 */

char	*ft_error_message(t_vars *vars)
{
	if (vars->c == 0)
		return ("\033[1;31m🛑ERROR:\nElement 'C' is missing.\033[0m\n");
	if (vars->p == 0)
		return ("\033[1;31m🛑ERROR:\nElement 'P' is missing.\033[0m\n");
	if (vars->p > 1)
		return ("\033[1;31m🛑ERROR:\n'P' > 1.\033[0m\n");
	if (vars->e == 0)
		return ("\033[1;31m🛑ERROR:\nElement 'Exit' is missing.\033[0m");
	if (vars->e > 1)
		return ("\033[1;31m🛑ERROR:\n'E' > 1.\033[0m\n");
	return (NULL);
}
