/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 10:15:43 by mzolotar          #+#    #+#             */
/*   Updated: 2025/06/03 07:56:14 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/cub3d.h"

/**
 * @brief Moves the player forward based on direction and speed.
 *
 * Adds a margin to prevent collision with walls during forward movement.
 *
 * @param game Pointer to the main game structure.
 * @return void
 */
void	move_forward(t_game *game)
{
	t_player	*p;
	double		next_x;
	double		next_y;
	double		margin_wall;

	p = &game->player;
	next_x = p->pos_x_player + p->dir_x_player * p->move_speed;
	next_y = p->pos_y_player + p->dir_y_player * p->move_speed;
	margin_wall = 0.1;
	if (game->map->map_str[(int)p->pos_y_player][(int)(next_x + (p->dir_x_player
			* margin_wall))] != '1')
		p->pos_x_player = next_x;
	if (game->map->map_str[(int)(next_y + (p->dir_y_player
				* margin_wall))][(int)p->pos_x_player] != '1')
		p->pos_y_player = next_y;
	re_draw_window(game);
}

/**
 * @brief Moves the player backward based on direction and speed.
 *
 * Uses a margin to ensure the player doesn't walk through walls.
 *
 * @param game Pointer to the main game structure.
 * @return void
 */
void	move_backward(t_game *game)
{
	t_player	*p;
	double		next_x;
	double		next_y;
	double		margin_wall;

	p = &game->player;
	next_x = p->pos_x_player - p->dir_x_player * p->move_speed;
	next_y = p->pos_y_player - p->dir_y_player * p->move_speed;
	margin_wall = 0.05;
	if (game->map->map_str[(int)p->pos_y_player][(int)(next_x - (p->dir_x_player
			* margin_wall))] != '1')
		p->pos_x_player = next_x;
	if (game->map->map_str[(int)(next_y - (p->dir_y_player
				* margin_wall))][(int)p->pos_x_player] != '1')
		p->pos_y_player = next_y;
	re_draw_window(game);
}

/**
 * @brief Moves the player to the left using the camera plane.
 *
 * Adds margin offset to avoid clipping into nearby walls.
 *
 * @param game Pointer to the main game structure.
 * @return void
 */
void	move_left(t_game *game)
{
	t_player	*p;
	double		next_x;
	double		next_y;
	double		margin_wall;

	p = &game->player;
	next_x = p->pos_x_player - p->plane_x_player * p->move_speed;
	next_y = p->pos_y_player - p->plane_y_player * p->move_speed;
	margin_wall = 0.15;
	if (game->map->map_str[(int)p->pos_y_player][(int)(next_x
		- (p->plane_x_player * margin_wall))] != '1')
		p->pos_x_player = next_x;
	if (game->map->map_str[(int)(next_y - (p->plane_y_player
				* margin_wall))][(int)p->pos_x_player] != '1')
		p->pos_y_player = next_y;
	re_draw_window(game);
}

/**
 * @brief Moves the player to the right using the camera plane.
 *
 * Prevents the player from moving into walls by checking with margin.
 *
 * @param game Pointer to the main game structure.
 * @return void
 */
void	move_right(t_game *game)
{
	t_player	*p;
	double		next_x;
	double		next_y;
	double		margin_wall;

	p = &game->player;
	next_x = p->pos_x_player + p->plane_x_player * p->move_speed;
	next_y = p->pos_y_player + p->plane_y_player * p->move_speed;
	margin_wall = 0.15;
	if (game->map->map_str[(int)p->pos_y_player][(int)(next_x
		+ (p->plane_x_player * margin_wall))] != '1')
		p->pos_x_player = next_x;
	if (game->map->map_str[(int)(next_y + (p->plane_y_player
				* margin_wall))][(int)p->pos_x_player] != '1')
		p->pos_y_player = next_y;
	re_draw_window(game);
}
