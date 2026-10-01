/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_gestor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 22:27:24 by mzolotar          #+#    #+#             */
/*   Updated: 2024/11/22 13:22:43 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/**
 * @brief Loads all game textures from files into image structures.
 *
 * @param vars Pointer to the game variables structure.
 * @return void This function does not return.
 */

void	file_to_image(t_vars *vars)
{
	int	a;

	a = XPM_SIZE;
	vars->img_render.empty = mlx_xpm_file_to_image(vars->mlx,
			"textures/flor_5.xpm", &a, &a);
	vars->img_render.wall = mlx_xpm_file_to_image(vars->mlx,
			"textures/wall_1.xpm", &a, &a);
	vars->img_render.exit1 = mlx_xpm_file_to_image(vars->mlx,
			"textures/exit_2.xpm", &a, &a);
	vars->img_render.exit2 = mlx_xpm_file_to_image(vars->mlx,
			"textures/exit_3.xpm", &a, &a);
	vars->img_render.collectible = mlx_xpm_file_to_image(vars->mlx,
			"textures/coin_6.xpm", &a, &a);
	file_to_image_player(vars);
}

/**
 * @brief Loads player textures into image structures.
 *
 * @param vars Pointer to the game variables structure.
 * @return void This function does not return.
 */

void	file_to_image_player(t_vars *vars)
{
	int	a;

	a = XPM_SIZE;
	vars->img_render.player_right = mlx_xpm_file_to_image(vars->mlx,
			"textures/player_r_2.xpm", &a, &a);
	vars->img_render.player_up = mlx_xpm_file_to_image(vars->mlx,
			"textures/player_u_2.xpm", &a, &a);
	vars->img_render.player_down = mlx_xpm_file_to_image(vars->mlx,
			"textures/player_d_1.xpm", &a, &a);
	vars->img_render.player_left = mlx_xpm_file_to_image(vars->mlx,
			"textures/player_l_2.xpm", &a, &a);
}

/**
 * @brief Returns the appropriate image based on map value and player state.
 *
 * @param map_value The map character (e.g., '1', 'C', 'P').
 * @param vars Pointer to the game variables structure.
 * @return char* The image to be rendered.
 */

char	*check_img_to_print(int map_value, t_vars *vars)
{
	if (map_value == '1')
		return (vars->img_render.wall);
	else if (map_value == 'C')
		return (vars->img_render.collectible);
	else if (map_value == 'P')
	{
		if (vars->player.direction == 'R')
			return (vars->img_render.player_right);
		else if (vars->player.direction == 'L')
			return (vars->img_render.player_left);
		else if (vars->player.direction == 'U')
			return (vars->img_render.player_up);
		else if (vars->player.direction == 'D')
			return (vars->img_render.player_down);
	}
	else if (map_value == '0')
		return (vars->img_render.empty);
	else if (map_value == 'E')
	{
		if (vars->player.exit_gest == 'C')
			return (vars->img_render.exit1);
		else if (vars->player.exit_gest == 'O')
			return (vars->img_render.exit2);
	}
	return (NULL);
}

/**
 * @brief Destroys all loaded images to free memory.
 *
 * @param vars Pointer to the game variables structure.
 * @return void This function does not return.
 */

void	destroy_images(t_vars *vars)
{
	if (vars->img_render.empty)
		mlx_destroy_image(vars->mlx, vars->img_render.empty);
	if (vars->img_render.wall)
		mlx_destroy_image(vars->mlx, vars->img_render.wall);
	if (vars->img_render.exit1)
		mlx_destroy_image(vars->mlx, vars->img_render.exit1);
	if (vars->img_render.exit2)
		mlx_destroy_image(vars->mlx, vars->img_render.exit2);
	if (vars->img_render.collectible)
		mlx_destroy_image(vars->mlx, vars->img_render.collectible);
	if (vars->img_render.player_right)
		mlx_destroy_image(vars->mlx, vars->img_render.player_right);
	if (vars->img_render.player_up)
		mlx_destroy_image(vars->mlx, vars->img_render.player_up);
	if (vars->img_render.player_down)
		mlx_destroy_image(vars->mlx, vars->img_render.player_down);
	if (vars->img_render.player_left)
		mlx_destroy_image(vars->mlx, vars->img_render.player_left);
}
