/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_texture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 10:02:48 by mzolotar          #+#    #+#             */
/*   Updated: 2025/08/11 08:24:40 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/cub3d.h"

/**
 * @brief Selects texture index based on ray collision direction.
 *
 * @param ray Pointer to the ray struct with collision info.
 * @return Index of the corresponding texture to use.
 */
int	select_texture(t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->ray_dir_x < 0)
			return (WEST);
		else
			return (EAST);
	}
	else
	{
		if (ray->ray_dir_y < 0)
			return (NORTH);
		else
			return (SOUTH);
	}
}

/**
 * @brief Retrieves texture data and computes texture X position.
 *
 * @param game Pointer to the main game struct.
 * @return Pointer to the texture image to be rendered.
 */
t_img	*get_texture_data(t_game *game)
{
	t_ray	*ray;
	double	wall_x;
	int		tex_num;
	t_img	*tex;

	ray = game->ray_struct;
	wall_x = calculate_wall_hit_position(game);
	tex_num = select_texture(ray);
	tex = game->textures[tex_num];
	ray->tex_x = (int)(wall_x * (double)(tex->img_width));
	if (tex_num == SOUTH || tex_num == WEST)
		ray->tex_x = tex->img_width - ray->tex_x - 1;
	return (tex);
}

/**
 * @brief Draws a textured vertical column on the screen.
 *
 * @param game Pointer to the main game struct.
 * @param tex Pointer to the texture image.
 * @param x X position of the column to draw.
 */
void	draw_textured_column(t_game *game, t_img *tex, int x)
{
	t_ray	*ray;
	int		y;
	int		tex_y;
	int		color;

	ray = game->ray_struct;
	ray->step = 1.0 * tex->img_height / ray->line_height;
	ray->tex_pos = (ray->draw_start - WIN_HEIGHT / 2 + ray->line_height / 2)
		* ray->step;
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		tex_y = (int)ray->tex_pos & (tex->img_height - 1);
		ray->tex_pos += ray->step;
		color = ((int *)tex->img_addr)[tex_y * tex->img_width + ray->tex_x];
		((int *)game->screen->img_addr)[y * WIN_WIDTH + x] = color;
		y++;
	}
}

/**
 * @brief Performs raycasting and renders the scene column by column.
 *
 * @param game Pointer to the main game struct.
 */
void	raycasting(t_game *game)
{
	int		x;
	t_img	*tex;

	x = 0;
	while (x < WIN_WIDTH)
	{
		init_ray_values(game, x);
		check_ray_direction(game);
		dda_algorithm(game);
		calculate_wall_data(game);
		tex = get_texture_data(game);
		draw_textured_column(game, tex, x);
		x++;
	}
}

/**
 * @brief Redraws the entire window with the current game state.
 *
 * @param game Pointer to the main game struct.
 */
void	re_draw_window(t_game *game)
{
	draw_background(game);
	raycasting(game);
	mlx_put_image_to_window(game->mlx, game->window, game->screen->img_ptr, 0,
		0);
}
