/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 23:26:55 by mzolotar          #+#    #+#             */
/*   Updated: 2024/11/22 13:30:20 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/**
 * @brief Resumes player movement based on key press and updates position.
 *
 * @param vars The game variables.
 * @param x The current x position.
 * @param y The current y position.
 * @param keycode The key pressed to move.
 * @return void
 */

static void	move_resume(t_vars *vars, int x, int y, int keycode)
{
	if (!vars)
		return ;
	if (keycode == KEY_CODE_UP || keycode == 65362)
		y -= 1;
	if (keycode == KEY_CODE_DOWN || keycode == 65364)
		y += 1;
	if (keycode == KEY_CODE_LEFT || keycode == 65361)
		x -= 1;
	if (keycode == KEY_CODE_RIGHT || keycode == 65363)
		x += 1;
	if (vars->map_data.split_strs[y][x] == 'E' && vars->c == 0)
	{
		winner_message();
		handle_exit(vars);
	}
	if (vars->map_data.split_strs[y][x] == 'C')
	{
		vars->map_data.split_strs[y][x] = '0';
		vars->c--;
	}
	else if (vars->map_data.split_strs[y][x] == '1')
		return ;
}

/**
 * @brief Moves the player up if possible and updates the game state.
 *
 * @param vars The game variables.
 * @return void
 */

void	move_up(t_vars *vars)
{
	int	x;
	int	y;

	x = vars->player.x_player;
	y = vars->player.y_player;
	if (y > 0 && vars->map_data.split_strs[y - 1][x] != '1')
	{
		move_resume(vars, x, y, KEY_CODE_UP);
		if (vars->map_data.split_strs[y - 1][x] == 'E' && (vars->c != 0
				|| vars->e == 1))
			return ;
		draw_texture_cell(vars, '0', XPM_SIZE * y, XPM_SIZE * x);
		vars->map_data.split_strs[y][x] = '0';
		y--;
		vars->player.direction = 'U';
		draw_texture_cell(vars, '0', XPM_SIZE * y, XPM_SIZE * x);
		draw_texture_cell(vars, 'P', XPM_SIZE * y, XPM_SIZE * x);
		vars->map_data.split_strs[y][x] = 'P';
		vars->movement++;
		ft_printf("movements: %i\n", vars->movement);
		if (vars->c == 0)
			draw_exit_open(vars);
		vars->player.y_player = y;
	}
}

/**
 * @brief Moves the player left if possible and updates the game state.
 *
 * @param vars The game variables.
 * @return void
 */

void	move_left(t_vars *vars)
{
	int	x;
	int	y;

	x = vars->player.x_player;
	y = vars->player.y_player;
	if (x > 0 && vars->map_data.split_strs[y][x - 1] != '1')
	{
		move_resume(vars, x, y, KEY_CODE_LEFT);
		if (vars->map_data.split_strs[y][x - 1] == 'E' && (vars->c != 0
				|| vars->e == 1))
			return ;
		draw_texture_cell(vars, '0', XPM_SIZE * y, XPM_SIZE * x);
		vars->map_data.split_strs[y][x] = '0';
		x--;
		vars->player.direction = 'L';
		draw_texture_cell(vars, '0', XPM_SIZE * y, XPM_SIZE * x);
		draw_texture_cell(vars, 'P', XPM_SIZE * y, XPM_SIZE * x);
		vars->map_data.split_strs[y][x] = 'P';
		vars->movement++;
		ft_printf("movements: %i\n", vars->movement);
		if (vars->c == 0)
			draw_exit_open(vars);
		vars->player.x_player = x;
	}
}
/**
 * @brief Moves the player down if possible and updates the game state.
 *
 * @param vars The game variables.
 * @return void
 */

void	move_down(t_vars *vars)
{
	int	x;
	int	y;

	x = vars->player.x_player;
	y = vars->player.y_player;
	if (x > 0 && vars->map_data.split_strs[y + 1][x] != '1')
	{
		move_resume(vars, x, y, KEY_CODE_DOWN);
		if (vars->map_data.split_strs[y + 1][x] == 'E' && (vars->c != 0
				|| vars->e == 1))
			return ;
		draw_texture_cell(vars, '0', XPM_SIZE * y, XPM_SIZE * x);
		vars->map_data.split_strs[y][x] = '0';
		y++;
		vars->player.direction = 'D';
		draw_texture_cell(vars, '0', XPM_SIZE * y, XPM_SIZE * x);
		draw_texture_cell(vars, 'P', XPM_SIZE * y, XPM_SIZE * x);
		vars->map_data.split_strs[y][x] = 'P';
		vars->movement++;
		ft_printf("movements: %i\n", vars->movement);
		if (vars->c == 0)
			draw_exit_open(vars);
		vars->player.y_player = y;
	}
}

/**
 * @brief Moves the player right if possible and updates the game state.
 *
 * @param vars The game variables.
 * @return void
 */

void	move_right(t_vars *vars)
{
	int	x;
	int	y;

	x = vars->player.x_player;
	y = vars->player.y_player;
	if (x > 0 && vars->map_data.split_strs[y][x + 1] != '1')
	{
		move_resume(vars, x, y, KEY_CODE_RIGHT);
		if (vars->map_data.split_strs[y][x + 1] == 'E' && (vars->c != 0
				|| vars->e == 1))
			return ;
		draw_texture_cell(vars, '0', XPM_SIZE * y, XPM_SIZE * x);
		vars->map_data.split_strs[y][x] = '0';
		x++;
		vars->player.direction = 'R';
		draw_texture_cell(vars, '0', XPM_SIZE * y, XPM_SIZE * x);
		draw_texture_cell(vars, 'P', XPM_SIZE * y, XPM_SIZE * x);
		vars->map_data.split_strs[y][x] = 'P';
		vars->movement++;
		ft_printf("movements: %i\n", vars->movement);
		if (vars->c == 0)
			draw_exit_open(vars);
		vars->player.x_player = x;
	}
}
