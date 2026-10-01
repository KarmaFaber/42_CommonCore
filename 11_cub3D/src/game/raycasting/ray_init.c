/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 10:02:44 by mzolotar          #+#    #+#             */
/*   Updated: 2025/08/11 08:24:18 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/cub3d.h"

/**
 * @brief Initializes ray direction and map position for current column.
 *
 * @param game Pointer to game structure containing player and ray data.
 * @param x Current screen column being processed.
 */
void	init_ray_values(t_game *game, int x)
{
	t_ray		*ray;
	t_player	*p;

	ray = game->ray_struct;
	p = &game->player;
	ray->camera_x = 2.0 * x / (double)WIN_WIDTH - 1.0;
	ray->ray_dir_x = p->dir_x_player + p->plane_x_player * ray->camera_x;
	ray->ray_dir_y = p->dir_y_player + p->plane_y_player * ray->camera_x;
	ray->map_x = (int)p->pos_x_player;
	ray->map_y = (int)p->pos_y_player;
	ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
	ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
	ray->hit = 0;
}

/**
 * @brief Calculates initial ray step and side distances.
 *
 * @param game Pointer to game structure containing ray and player data.
 */
void	check_ray_direction(t_game *game)
{
	if (game->ray_struct->ray_dir_x < 0)
	{
		game->ray_struct->step_x = -1;
		game->ray_struct->side_dist_x = (game->player.pos_x_player
				- game->ray_struct->map_x) * game->ray_struct->delta_dist_x;
	}
	else
	{
		game->ray_struct->step_x = 1;
		game->ray_struct->side_dist_x = (game->ray_struct->map_x + 1.0
				- game->player.pos_x_player) * game->ray_struct->delta_dist_x;
	}
	if (game->ray_struct->ray_dir_y < 0)
	{
		game->ray_struct->step_y = -1;
		game->ray_struct->side_dist_y = (game->player.pos_y_player
				- game->ray_struct->map_y) * game->ray_struct->delta_dist_y;
	}
	else
	{
		game->ray_struct->step_y = 1;
		game->ray_struct->side_dist_y = (game->ray_struct->map_y + 1.0
				- game->player.pos_y_player) * game->ray_struct->delta_dist_y;
	}
}

/**
 * @brief Performs the DDA algorithm to detect wall collisions.
 *
 * @param game Pointer to game structure containing ray and map data.
 */
void	dda_algorithm(t_game *game)
{
	t_ray	*ray;

	ray = game->ray_struct;
	while (ray->hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (game->map->map_str[ray->map_y][ray->map_x] == '1')
			ray->hit = 1;
	}
}

/**
 * @brief Calculates perpendicular wall distance and screen draw limits.
 *
 * @param game Pointer to game structure containing ray and player data.
 */
void	calculate_wall_data(t_game *game)
{
	t_ray		*ray;
	t_player	*p;

	ray = game->ray_struct;
	p = &game->player;
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->map_x - p->pos_x_player + (1 - ray->step_x)
				/ 2) / ray->ray_dir_x;
	else
		ray->perp_wall_dist = (ray->map_y - p->pos_y_player + (1 - ray->step_y)
				/ 2) / ray->ray_dir_y;
	ray->line_height = (int)(WIN_HEIGHT / ray->perp_wall_dist);
	ray->draw_start = -ray->line_height / 2 + WIN_HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + WIN_HEIGHT / 2;
	if (ray->draw_end >= WIN_HEIGHT)
		ray->draw_end = WIN_HEIGHT - 1;
}

/**
 * @brief Calculates exact wall hit position for texture mapping.
 *
 * @param game Pointer to game structure with ray and player information.
 * @return Normalized wall hit position on the x or y axis.
 */
double	calculate_wall_hit_position(t_game *game)
{
	t_ray		*ray;
	t_player	*p;
	double		wall_x;

	ray = game->ray_struct;
	p = &game->player;
	if (ray->side == 0)
		wall_x = p->pos_y_player + ray->perp_wall_dist * ray->ray_dir_y;
	else
		wall_x = p->pos_x_player + ray->perp_wall_dist * ray->ray_dir_x;
	return (wall_x - floor(wall_x));
}
