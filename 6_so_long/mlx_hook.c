/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 17:36:39 by mzolotar          #+#    #+#             */
/*   Updated: 2024/11/22 13:19:28 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/**
 * @brief Cleans up resources and exits the program gracefully.
 *
 * @param vars Pointer to the game variables structure.
 * @return int This function does not return; it exits the program.
 */

int	handle_exit(t_vars *vars)
{
	if (!vars)
		exit(0);
	destroy_images(vars);
	ft_free_map_data(&vars->map_data);
	if (vars->map_path)
	{
		free(vars->map_path);
		vars->map_path = NULL;
	}
	if (vars->win)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		vars->win = NULL;
	}
	if (vars->mlx)
	{
		mlx_destroy_display(vars->mlx);
		free(vars->mlx);
		vars->mlx = NULL;
	}
	exit(0);
}

/**
 * @brief Handles the close event triggered by a specific key press.
 *
 * @param keycode Key code for triggering the close event.
 * @param vars Pointer to the game variables structure.
 * @return int Always returns 0.
 */

int	handle_close(int keycode, t_vars *vars)
{
	if (keycode == KEY_CODE_EXIT)
	{
		exit_message();
		handle_exit(vars);
	}
	return (0);
}

/**
 * @brief Processes keyboard input and triggers corresponding actions.
 *
 * @param keycode Key code for the pressed key.
 * @param vars Pointer to the game variables structure.
 * @return int Always returns 0.
 */

int	key_hook(int keycode, t_vars *vars)
{
	if (keycode == KEY_CODE_UP || keycode == 65362)
		move_up(vars);
	if (keycode == KEY_CODE_LEFT || keycode == 65361)
		move_left(vars);
	if (keycode == KEY_CODE_DOWN || keycode == 65364)
		move_down(vars);
	if (keycode == KEY_CODE_RIGHT || keycode == 65363)
		move_right(vars);
	if (keycode == KEY_CODE_EXIT)
		handle_close(KEY_CODE_EXIT, vars);
	return (0);
}

/**
 * @brief Handles window close events and exits the program.
 *
 * @param vars Pointer to the game variables structure.
 * @return int Always returns 0.
 */

int	close_window(t_vars *vars)
{
	exit_message();
	handle_exit(vars);
	return (0);
}
