/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 09:16:55 by mzolotar          #+#    #+#             */
/*   Updated: 2025/08/06 19:37:52 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
# define GAME_H

/*** Includes cub3d ***/
# include "../inc/cub3d.h"
# include "../libft/inc/libft.h"

/*** Prototypes ***/
// src/game/game_loop.c
//static void	wind_err_and_exit(t_game *game);
//static void	check_wind_size(t_game *game);
void			start_game_loop_init(t_game *game);
void			start_game_loop(t_game *game);

// src/game/raycasting/ray_init.c
void			init_ray_values(t_game *game, int x);
void			check_ray_direction(t_game *game);
void			dda_algorithm(t_game *game);
void			calculate_wall_data(t_game *game);
double			calculate_wall_hit_position(t_game *game);

// src/game/raycasting/ray_texture.c
int				select_texture(t_ray *ray);
t_img			*get_texture_data(t_game *game);
void			draw_textured_column(t_game *game, t_img *tex, int x);
void			raycasting(t_game *game);
void			re_draw_window(t_game *game);

// src/game/render/background.c
int				get_background_color(t_game *game, int y, int half);
void			draw_background(t_game *game);

// src/game/init/player_setup.c
void			set_direction_north_south(t_player *player, char dir);
void			set_direction_east_west(t_player *player, char dir);
void			scan_player(t_game *game);

// src/game/init/textures.c
void			check_file_to_image(t_img *tex, t_game *game, char *texture);
void			file_to_image(t_game *game);

// src/game/input/player_movement.c
void			move_forward(t_game *game);
void			move_backward(t_game *game);
void			move_left(t_game *game);
void			move_right(t_game *game);

// src/game/input/camera_movement.c
void			move_camara_left(t_game *game);
void			move_camara_right(t_game *game);
int				key_hook(int keycode, t_game *game);

// src/errors/error_exit.c
void			exit_message(void);
int				handle_exit(t_game *game, int exit_code);
int				close_window(t_game *game);
void			destroy_images(t_game *game);

#endif