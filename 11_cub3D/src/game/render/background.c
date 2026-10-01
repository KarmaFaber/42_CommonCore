/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdiaz-he <jdiaz-he@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 10:08:07 by mzolotar          #+#    #+#             */
/*   Updated: 2025/06/12 14:44:42 by jdiaz-he         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/cub3d.h"

/**
 * @brief Returns the RGB color for ceiling or floor based on y position.
 *
 * @param game Pointer to the game struct containing color info.
 * @param y The current vertical pixel position being processed.
 * @param half The midpoint of the screen height.
 * @return The RGB color value as a 24-bit integer.
 */
int	get_background_color(t_game *game, int y, int half)
{
	int	r;
	int	g;
	int	b;

	if (y < half)
	{
		r = game->file->c_ceiling.red;
		g = game->file->c_ceiling.green;
		b = game->file->c_ceiling.blue;
	}
	else
	{
		r = game->file->c_floor.red;
		g = game->file->c_floor.green;
		b = game->file->c_floor.blue;
	}
	return ((r << 16) | (g << 8) | b);
}

/**
 * @brief Fills the screen buffer with ceiling and floor background colors.
 *
 * @param game Pointer to the game struct containing the screen buffer.
 * @return void
 */
void	draw_background(t_game *game)
{
	int	y;
	int	x;
	int	half;
	int	color;

	y = 0;
	half = WIN_HEIGHT / 2;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		color = get_background_color(game, y, half);
		while (x < WIN_WIDTH)
		{
			((int *)game->screen->img_addr)[y * WIN_WIDTH + x] = color;
			x++;
		}
		y++;
	}
}
