/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 20:30:32 by mzolotar          #+#    #+#             */
/*   Updated: 2024/11/27 10:39:50 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/**
 * @brief Draws a row of textures to the window based on the map row.
 *
 * @param vars Pointer to the game variables structure.
 * @param row The map row to be drawn.
 * @param pixls_y The y-coordinate to start drawing.
 * @return void This function does not return.
 */

void	draw_texture_row(t_vars *vars, char *row, int pixls_y)
{
	int	j;
	int	pixls_x;

	j = 0;
	pixls_x = 0;
	while (row[j] && row != NULL)
	{
		draw_texture_cell(vars, row[j], pixls_y, pixls_x);
		j++;
		pixls_x += XPM_SIZE;
	}
}

/**
 * @brief Draws a single texture cell to the window.
 *
 * @param vars Pointer to the game variables structure.
 * @param cell The map element representing the texture.
 * @param pixls_x The x-coordinate to start drawing.
 * @param pixls_y The y-coordinate to start drawing.
 * @return void This function does not return.
 */

void	draw_texture_cell(t_vars *vars, char cell, int pixls_x, int pixls_y)
{
	vars->img = check_img_to_print(cell, vars);
	if (!vars->img)
	{
		ft_error(vars, "\033[1;31m🛑ERROR:\nFailed to load image.\033[0m\n");
		ft_free_map_data(&vars->map_data);
		return ;
	}
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img, pixls_y, pixls_x);
}

/**
 * @brief Prints the textures for the map to the window.
 *
 * @param vars Pointer to the game variables structure.
 * @param split_strs The map data split into rows.
 * @param down The number of rows to be printed.
 * @return void This function does not return.
 */

void	print_textures(t_vars *vars, char **split_strs, int down)
{
	int	i;
	int	pixls_y;

	if (!split_strs)
	{
		ft_error(vars, "\033[1;31m🛑ERROR:\nMap is empty or invalid\033[0m\n");
		return ;
	}
	i = 0;
	pixls_y = 0;
	while (i <= down)
	{
		if (split_strs[i] == NULL)
		{
			return ;
		}
		draw_texture_row(vars, split_strs[i], pixls_y);
		i++;
		pixls_y += XPM_SIZE;
	}
}
