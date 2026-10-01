/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 09:47:45 by jdiaz-he          #+#    #+#             */
/*   Updated: 2025/08/11 08:25:30 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

/**
 * @brief Handles errors during MLX initialization and exits the game.
 *
 * Prints an error message indicating failure to initialize MLX components,
 * frees allocated resources, and exits the game with a failure status.
 *
 * @param game Pointer to the main game structure containing all data.
 * @return void
 */
static void	wind_err_and_exit(t_game *game)
{
	ft_puterr(CRED"Error:\nFailed to initialize MLX components.\n");
	print_malloc_error(__FILE__, __LINE__);
	handle_exit(game, 1);
}

/**
 * @brief Checks if the window size exceeds maximum limits.
 *
 * Validates the window dimensions against predefined maximum values.
 * If the dimensions are invalid, it prints an error message and exits.
 *
 * @param game Pointer to the main game structure containing all data.
 * @return void
 */
static void	check_wind_size(t_game *game)
{
	if (WIN_WIDTH > MAX_WIDTH_WIN || WIN_HEIGHT > MAX_HEIGHT_WIN)
	{
		ft_puterr(CRED"Error:\nWindow size exceeds maximum limits.\n");
		handle_exit(game, 1);
	}
	if (WIN_WIDTH <= 0 || WIN_HEIGHT <= 0)
	{
		ft_puterr(CRED"Error:\nWindow size must be positive.\n");
		handle_exit(game, 1);
	}
	if ((long)WIN_WIDTH * (long)WIN_HEIGHT * 4 > INT_MAX)
	{
		ft_puterr(CRED"Error:\nWindow size too large, would cause overflow.\n");
		handle_exit(game, 1);
	}
}

/**
 * @brief Initializes the MLX context, window, and screen buffer.
 *
 * Sets up the MLX environment, creates a new window, and allocates
 * memory for the screen image. If any step fails, it exits with an error.
 *
 * @param game Pointer to the main game structure containing all data.
 * @return void
 */
void	start_game_loop_init(t_game *game)
{
	check_wind_size(game);
	game->mlx = mlx_init();
	if (game->mlx)
		game->window = mlx_new_window(game->mlx,
				WIN_WIDTH, WIN_HEIGHT, "cub3D");
	if (game->mlx && game->window && game->screen)
	{
		if (WIN_WIDTH > 0 && WIN_HEIGHT > 0
			&& WIN_WIDTH <= MAX_WIDTH_WIN && WIN_HEIGHT <= MAX_HEIGHT_WIN)
			game->screen->img_ptr = mlx_new_image(game->mlx,
					WIN_WIDTH, WIN_HEIGHT);
		else
			game->screen->img_ptr = NULL;
	}
	if (game->screen->img_ptr)
		game->screen->img_addr = mlx_get_data_addr(game->screen->img_ptr,
				&game->screen->bits_per_pixel, &game->screen->line_length,
				&game->screen->endian);
	if (!game->mlx || !game->window
		|| !game->screen->img_ptr || !game->screen->img_addr)
		wind_err_and_exit(game);
}

/**
 * @brief Initializes and starts the main rendering loop of the game.
 *
 * Sets up the MLX context, window, screen buffer, loads textures,
 * prepares the player and map data, hooks input events, and starts
 * the continuous rendering loop via mlx_loop().
 *
 * @param game Pointer to the main game structure containing all data.
 * @return void
 */
void	start_game_loop(t_game *game)
{
	start_game_loop_init(game);
	file_to_image(game);
	scan_player(game);
	re_draw_window(game);
	mlx_hook(game->window, 17, 0, close_window, game);
	mlx_key_hook(game->window, key_hook, game);
	mlx_loop(game->mlx);
}
