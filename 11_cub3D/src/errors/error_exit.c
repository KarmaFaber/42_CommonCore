/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 10:19:28 by mzolotar          #+#    #+#             */
/*   Updated: 2025/08/04 09:13:17 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

/**
 * @brief Prints a message when the player exits the game.
 *
 * @param void No parameters are used in this function.
 * @return void This function does not return.
 */
void	exit_message(void)
{
	printf("\033[1;33m\033[0m\n");
	printf("--------------------------------------------------\n");
	printf("|              You gave up 🙁                    |\n");
	printf("|   Is the game hard for you? Try again......    |\n");
	printf("--------------------------------------------------\n");
}

/**
 * @brief Frees resources and exits the game with given code.
 *
 * @param game Pointer to the main game structure.
 * @param exit_code Exit status code for the program.
 * @return int This function does not return.
 */
int	handle_exit(t_game *game, int exit_code) // revisar
{
	if (!game)
		exit(0);
	destroy_images(game);
	if (game->mlx && game->window)
		mlx_destroy_window(game->mlx, game->window);
	if (game->mlx)
		mlx_destroy_display(game->mlx);
	free_tgame(game);
	exit(exit_code);
}

/**
 * @brief Handles window close events and exits the program.
 *
 * @param game Pointer to the game variables structure.
 * @return int Always returns 0.
 */
int	close_window(t_game *game)
{
	exit_message();
	handle_exit(game, 0);
	return (0);
}

/**
 * @brief Frees all loaded images from memory using MLX functions.
 *
 * Destroys texture images and the screen image if they exist.
 *
 * @param game Pointer to the main game structure.
 * @return void
 */
void	destroy_images(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (game->textures[i]->img_ptr)
			mlx_destroy_image(game->mlx, game->textures[i]->img_ptr);
		i++;
	}
	if (game->screen && game->screen->img_ptr)
		mlx_destroy_image(game->mlx, game->screen->img_ptr);
}
