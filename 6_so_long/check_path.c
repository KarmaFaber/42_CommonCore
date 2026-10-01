/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 19:48:32 by mzolotar          #+#    #+#             */
/*   Updated: 2024/11/27 11:56:57 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/**
 * @brief Scans the map to find the player's position.
 *
 * @param vars The game variables structure.
 * @param str_to_path The map data as a 2D string array.
 * @return void This function does not return.
 */

void	scan_player(t_vars *vars, char **str_to_path)
{
	int	y;
	int	x;

	vars->player.y_player = 0;
	vars->player.x_player = 0;
	y = 0;
	while (y < vars->x)
	{
		x = 0;
		while (x < vars->y)
		{
			if (str_to_path[y][x] == 'P')
			{
				vars->player.y_player = y;
				vars->player.x_player = x;
				return ;
			}
			x++;
		}
		y++;
	}
	ft_error(vars, "\033[1;31m🛑ERROR:\nThe player was not found.\033[0m\n");
	vars->player.y_player = 0;
	vars->player.x_player = 0;
}

/**
 * @brief Recursively marks paths, collectibles, and exits as visited.
 *
 * @param x The x-coordinate of the current position.
 * @param y The y-coordinate of the current position.
 * @param map_copy The map copy to modify.
 * @param vars The game variables structure.
 * @return void This function does not return.
 */

void	move_on_paths(int x, int y, char **map_copy, t_vars *vars)
{
	char	type;

	if (x < 0 || y < 0 || y >= vars->x || x >= vars->y)
		return ;
	type = map_copy[y][x];
	if (type == 'C')
	{
		vars->c_check -= 1;
		map_copy[y][x] = '1';
	}
	else if (type == 'E')
	{
		vars->e_check -= 1;
		map_copy[y][x] = '1';
	}
	else if (type == '0' || type == 'P')
	{
		map_copy[y][x] = '1';
	}
	else
		return ;
	move_on_paths(x + 1, y, map_copy, vars);
	move_on_paths(x - 1, y, map_copy, vars);
	move_on_paths(x, y + 1, map_copy, vars);
	move_on_paths(x, y - 1, map_copy, vars);
}

/**
 * @brief Checks if the player can access all paths, collectibles, and exits.
 *
 * @param vars The game variables structure.
 * @return void This function does not return.
 */

void	check_valid_path(t_vars *vars)
{
	vars->c_check = vars->c;
	vars->e_check = vars->e;
	vars->map_data.map_copy = ft_copy_split(vars->map_data.split_strs);
	if (!vars->map_data.map_copy)
		ft_error(vars,
			"\033[1;31m🛑ERROR:\nCouldn't make a copy of the map.\033[0m\n");
	scan_player(vars, vars->map_data.map_copy);
	if (vars->player.y_player >= vars->win_height
		|| vars->player.x_player >= vars->win_width)
		ft_error(vars,
			"\033[1;31m🛑ERROR:\nPlayer position out of bounds.\033[0m\n");
	move_on_paths(vars->player.x_player, vars->player.y_player,
		vars->map_data.map_copy, vars);
	if (!vars)
		return ;
	if (vars->c_check > 0)
		ft_error(vars, "\033[1;31m🛑ERROR:\nNot all 'C' were finded.\033[0m\n");
	if (vars->e_check > 0)
		ft_error(vars, "\033[1;31m🛑ERROR:\nNot all exit were finded.\033[0m\n");
	ft_free_split_strs(vars->map_data.map_copy);
	vars->map_data.map_copy = NULL;
}

/**
 * @brief Scans the map to find the exit position.
 *
 * @param vars The game variables structure.
 * @param str_to_path The map data as a 2D string array.
 * @return void This function does not return.
 */

void	scan_exit(t_vars *vars, char **str_to_path)
{
	int	y;
	int	x;

	vars->player.y_exit = 0;
	vars->player.x_exit = 0;
	y = 0;
	while (y < vars->x)
	{
		x = 0;
		while (x < vars->y)
		{
			if (str_to_path[y][x] == 'E')
			{
				vars->player.y_exit = y;
				vars->player.x_exit = x;
				return ;
			}
			x++;
		}
		y++;
	}
	ft_error(vars, "\033[1;31m🛑ERROR:\nThe exit was not found.\033[0m\n");
	vars->player.y_exit = 0;
	vars->player.x_exit = 0;
}

/**
 * @brief Draws the exit when it is open.
 *
 * @param vars The game variables structure.
 * @return void This function does not return.
 */

void	draw_exit_open(t_vars *vars)
{
	int	x;
	int	y;
	int	pixls_x_exit;
	int	pixls_y_exit;

	y = vars->player.y_exit;
	x = vars->player.x_exit;
	vars->player.exit_gest = 'O';
	pixls_x_exit = XPM_SIZE * x;
	pixls_y_exit = XPM_SIZE * y;
	draw_texture_cell(vars, 'E', pixls_y_exit, pixls_x_exit);
}
