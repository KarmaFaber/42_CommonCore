/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_game.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdiaz-he <jdiaz-he@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 00:18:08 by jdiaz-he          #+#    #+#             */
/*   Updated: 2025/06/08 12:57:45 by jdiaz-he         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

t_game	*new_tgame(void)
{
	t_game	*game;

	game = (t_game *)ft_calloc(1, sizeof(t_game));
	if (!game)
	{
		print_malloc_error(__FILE__, __LINE__);
		exit(EXIT_FAILURE);
	}
	return (game);
}

// error_msg needs to be initialized with "Error:\n"
// window_width and window_height are not used in this version
int	init_tgame(t_game *game)
{
	if (!game)
		return (1);
	game->file = new_tcubfile();
	init_tcubfile(game->file);
	if (!game->file || !game->file->map)
		return (1);
	game->map = game->file->map;
	game->error_msg = ft_strdup(CRED ERROR);
	if (!game->error_msg)
		print_malloc_error(__FILE__, __LINE__);
	game->mlx = NULL;
	game->window = NULL;
	init_tplayer(&game->player);
	if (init_tgame_visuals(game))
		return (1);
	return (0);
}

int	init_tgame_visuals(t_game *game)
{
	if (!game)
		return (1);
	game->ray_struct = new_tray();
	init_tray(game->ray_struct);
	game->screen = new_timg();
	init_timg(game->screen);
	game->textures[NORTH] = new_timg();
	init_timg(game->textures[NORTH]);
	game->textures[SOUTH] = new_timg();
	init_timg(game->textures[SOUTH]);
	game->textures[EAST] = new_timg();
	init_timg(game->textures[EAST]);
	game->textures[WEST] = new_timg();
	init_timg(game->textures[WEST]);
	if (!game->ray_struct || !game->screen
		|| !game->textures[NORTH] || !game->textures[SOUTH]
		|| !game->textures[EAST] || !game->textures[WEST])
		return (1);
	return (0);
}

// game->mlx is adjusted in handle_exit
// game->window is freed when the window is closed with mlx_destroy_window
// game->ray_struct is freed with mlx??
void	free_tgame(t_game *game)
{
	if (!game)
		return ;
	if (game->file)
		free_tcubfile(game->file);
	if (game->map)
		free_tmap(game->map);
	free(game->error_msg);
	free(game->mlx);
	free_timg(game->screen);
	free_timg(game->textures[NORTH]);
	free_timg(game->textures[SOUTH]);
	free_timg(game->textures[EAST]);
	free_timg(game->textures[WEST]);
	free(game->img_struct);
	free(game->ray_struct);
	free(game);
}

void	free_exit_tgame(t_game *game, int status)
{
	free_tgame(game);
	exit(status);
}
