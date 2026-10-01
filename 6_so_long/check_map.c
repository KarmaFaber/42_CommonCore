/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 20:48:36 by mzolotar          #+#    #+#             */
/*   Updated: 2024/11/27 10:37:15 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/**
 * @brief Validates map data and checks if the map is correct.
 *
 * @param vars The game variables.
 * @return void
 */

void	check_map_valid(t_vars *vars)
{
	char	*error_message;

	if (!vars)
		ft_error(vars, "\033[1;31m🛑ERROR:\nInvalid map variables\033[0m\n");
	if (!vars->map_data.str_map)
		ft_error(vars, "\033[1;31m🛑ERROR:\nMap data not initialized.\033[0m\n");
	if (ft_strlen(vars->map_data.str_map) <= 1)
		ft_error(vars, "\033[1;31m🛑ERROR:\nMap is empty or invalid.\033[0m\n");
	if (vars->win_height == 0 || vars->win_width == 0)
		ft_error(vars,
			"\033[1;31m🛑ERROR:\nWindow dim. not initial. correctly.\033[0m\n");
	check_first_and_last_row_walls(vars->map_data.split_strs, vars);
	check_intermediate_row_walls(vars->map_data.split_strs, vars);
	check_is_rectangular(vars->map_data.split_strs, vars);
	error_message = ft_error_message(vars);
	if (error_message)
	{
		ft_error(vars, error_message);
	}
}
