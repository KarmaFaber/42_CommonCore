/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 07:39:18 by mzolotar          #+#    #+#             */
/*   Updated: 2024/11/27 10:42:23 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/**
 * @brief Initializes variables for the game map and player states.
 *
 * @param vars Pointer to the game variables structure.
 * @return void
 */

static void	map_initializer_vars(t_vars *vars)
{
	if (!vars)
	{
		ft_printf("\033[1;31m🛑ERROR:\n Initialising variebles.\033[0m\n");
		return ;
	}
	vars->player.y_player = 0;
	vars->player.x_player = 0;
	vars->player.y_exit = 0;
	vars->player.x_exit = 0;
	vars->player.direction = 'D';
	vars->player.exit_gest = 'C';
	vars->c = 0;
	vars->p = 0;
	vars->e = 0;
	vars->e_check = 0;
	vars->c_check = 0;
	vars->x = 0;
	vars->y = 0;
	vars->movement = 0;
}

/**
 * @brief Initializes variables for the MLX library and map images.
 *
 * @param vars Pointer to the game variables structure.
 * @return void
 */

static void	map_initializer_img(t_vars *vars)
{
	vars->mlx = NULL;
	vars->img = NULL;
	vars->win = NULL;
	vars->img_width = 0;
	vars->img_height = 0;
	vars->win_width = 0;
	vars->win_height = 0;
	vars->map_path = NULL;
	vars->map_data.str_map = NULL;
	vars->map_data.split_strs = NULL;
	vars->map_data.map_copy = NULL;
	vars->img_render.empty = NULL;
	vars->img_render.wall = NULL;
	vars->img_render.exit1 = NULL;
	vars->img_render.exit2 = NULL;
	vars->img_render.collectible = NULL;
	vars->img_render.player_right = NULL;
	vars->img_render.player_up = NULL;
	vars->img_render.player_down = NULL;
	vars->img_render.player_left = NULL;
}

/**
 * @brief Sets up the game variables, map data, and validates the map.
 *
 * @param vars Pointer to the game variables structure.
 * @param filename Name of the map file to load.
 * @return void
 */

void	initialize_game(t_vars *vars, char *filename)
{
	map_initializer_vars(vars);
	map_initializer_img(vars);
	vars->map_path = ft_strjoin("maps/", filename);
	if (!vars->map_path)
		ft_error(NULL,
			"\033[1;31m🛑ERROR:\nFailed to initialize map path.\033[0m\n");
	vars->map_data = ft_create_map_data(vars, &vars->map_data);
	if (!vars->map_data.str_map || !vars->map_data.split_strs)
		ft_error(NULL,
			"\033[1;31m🛑ERROR:\nFailed to initialize map data.\033[0m\n");
	ft_fill_map_vars(vars->map_data.str_map, vars->map_data.split_strs, vars);
	fill_window_size(vars);
	check_map_valid(vars);
	check_valid_path(vars);
}

/**
 * @brief Starts the game loop, initializing MLX and handling events.
 *
 * @param vars Pointer to the game variables structure.
 * @return void
 */

void	start_game_loop(t_vars *vars)
{
	vars->mlx = mlx_init();
	vars->win = mlx_new_window(vars->mlx, vars->win_width, vars->win_height,
			"so_long");
	if (!vars->mlx || !vars->win)
	{
		ft_error(NULL, "\033[1;31m🛑ERROR:\nMLX or Win. init. failed.\033[0m\n");
		ft_free_map_data(&vars->map_data);
		return ;
	}
	file_to_image(vars);
	print_textures(vars, vars->map_data.split_strs, vars->x);
	scan_player(vars, vars->map_data.split_strs);
	scan_exit(vars, vars->map_data.split_strs);
	mlx_hook(vars->win, 17, 0, close_window, vars);
	mlx_key_hook(vars->win, key_hook, vars);
	mlx_loop(vars->mlx);
}

int	main(int argc, char *argv[])
{
	t_vars	vars;

	if (argc != 2)
		return (handle_argument_error());
	if (!is_valid_file_type(argv[1]))
		return (handle_invalid_file_error());
	initialize_game(&vars, argv[1]);
	start_game_loop(&vars);
	return (0);
}
