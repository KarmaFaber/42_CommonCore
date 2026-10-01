/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_setup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 10:11:20 by mzolotar          #+#    #+#             */
/*   Updated: 2025/08/08 08:07:44 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/cub3d.h"

/**
 * @brief Sets player direction and camera plane for North or South.
 *
 * Adjusts direction vector and camera plane based on orientation.
 *
 * @param player Pointer to the player structure.
 * @param dir Direction character ('N' or 'S').
 * @return void
 */
void	set_direction_north_south(t_player *player, char dir)
{
	if (dir == 'N')
	{
		player->dir_x_player = 0;
		player->dir_y_player = -1;
		player->plane_x_player = 0.66;
		player->plane_y_player = 0;
	}
	else
	{
		player->dir_x_player = 0;
		player->dir_y_player = 1;
		player->plane_x_player = -0.66;
		player->plane_y_player = 0;
	}
}

/**
 * @brief Sets player direction and camera plane for East or West.
 *
 * Adjusts direction vector and camera plane based on orientation.
 *
 * @param player Pointer to the player structure.
 * @param dir Direction character ('E' or 'W').
 * @return void
 */
void	set_direction_east_west(t_player *player, char dir)
{
	if (dir == 'E')
	{
		player->dir_x_player = 1;
		player->dir_y_player = 0;
		player->plane_x_player = 0;
		player->plane_y_player = 0.66;
	}
	else
	{
		player->dir_x_player = -1;
		player->dir_y_player = 0;
		player->plane_x_player = 0;
		player->plane_y_player = -0.66;
	}
}

/**
 * @brief Initializes player's position and direction in the game world.
 *
 * Converts map coordinates to game units and sets direction vectors.
 *
 * @param game Pointer to the main game structure.
 * @return void
 */
void	scan_player(t_game *game)
{
	t_player	*player;
	t_map		*map;
	char		dir;

	map = game->map;
	player = &game->player;
	player->pos_x_player = map->player_x + 0.5;
	player->pos_y_player = map->player_y + 0.5;
	dir = map->player_dir;
	if (dir == 'N' || dir == 'S')
		set_direction_north_south(player, dir);
	else
		set_direction_east_west(player, dir);
}
