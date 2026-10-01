/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 10:32:48 by mzolotar          #+#    #+#             */
/*   Updated: 2024/11/27 09:56:55 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

/* ********** includes ********** */
# include "libft/libft.h"
# include <fcntl.h>
# include <mlx.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

/* ** defines to make work easier ** */
# define XPM_SIZE 60
# define MAX_WIDTH_WIN 1920
# define MAX_HEIGHT_WIN 1080

# define KEY_CODE_UP 119
# define KEY_CODE_DOWN 115
# define KEY_CODE_LEFT 97
# define KEY_CODE_RIGHT 100
# define KEY_CODE_EXIT 65307

/* struct for storing split variables */
typedef struct s_map_data
{
	char		*str_map;
	char		**split_strs;
	char		**map_copy;
}				t_map_data;

/* struct for storing player position variables */
typedef struct s_player
{
	int			y_player;
	int			x_player;
	int			y_exit;
	int			x_exit;
	char		direction;
	char		exit_gest;

}				t_player;

/* struct for storing player position variables */
typedef struct s_img
{
	void		*empty;
	void		*collectible;
	void		*wall;
	void		*exit1;
	void		*exit2;
	void		*player_left;
	void		*player_right;
	void		*player_up;
	void		*player_down;
}				t_img;

/* struct to hand all of my programms data between functions */
typedef struct s_vars
{
	void		*mlx;
	void		*img;
	void		*win;
	int			img_width;
	int			img_height;
	int			win_width;
	int			win_height;
	int			movement;
	int			c;
	int			p;
	int			e;
	int			e_check;
	int			c_check;
	int			x;
	int			y;
	char		*map_path;
	t_map_data	map_data;
	t_player	player;
	t_img		img_render;
}				t_vars;

/* List the function I am using in the program: */

// so_long.c.c (5/5)
// static void	map_initializer(t_vars *vars);
// static void map_initializer_img(t_vars *vars);
void			initialize_game(t_vars *vars, char *filename);
void			start_game_loop(t_vars *vars);
// int main(int argc, char *argv[]);

// map_utils.c (4/5)
char			*read_map_line(int fd);
size_t			ft_map_size(t_vars *vars);
void			fill_window_size(t_vars *vars);
void			ft_fill_map_vars(const char *str, char **split_strs,
					t_vars *vars);

// ft_read_map.c   (5/5)
void			process_and_fill_map_line(char *line, char *str_map,
					size_t *index);
void			ft_read_and_fill_map(int fd, char *str_map, t_vars *vars);
char			*ft_create_str_map(size_t size, t_vars *vars);
t_map_data		ft_create_map_data(t_vars *vars, t_map_data *map_data);
char			**ft_split_map(char const *str_map, t_vars *vars);

// read_map_utils.c (3/5)
int				open_map_file(t_vars *vars);
char			*allocate_map_memory(size_t size, t_vars *vars);
void			verify_map_not_empty(char *str_map, t_vars *vars);

// check_map_utils.c (5/5)
void			check_is_rectangular(char **split_strs, t_vars *vars);
// static void	check_first_row_walls(char *first_row, t_vars *vars);
// static void	check_last_row_walls(char *last_row, t_vars *vars);
void			check_first_and_last_row_walls(char **split_strs, t_vars *vars);
void			check_intermediate_row_walls(char **split_strs, t_vars *vars);

// check_map.c (1/5)
void			check_map_valid(t_vars *vars);

// error_gestor.c		(5/5)
void			ft_free_map_data(t_map_data *map_data);
void			ft_free_str_map(char *str_map);
void			ft_free_split_strs(char **split_strs);
void			ft_error(t_vars *vars, char *err);
char			*ft_error_message(t_vars *vars);

// mlx_hook.c: (4/5)
int				handle_exit(t_vars *vars);
int				handle_close(int keycode, t_vars *vars);
int				key_hook(int keycode, t_vars *vars);
int				close_window(t_vars *vars);

// render_map.c (3/5)
void			draw_texture_row(t_vars *vars, char *row, int pixls_x);
void			draw_texture_cell(t_vars *vars, char cell, int pixls_x,
					int pixls_y);
void			print_textures(t_vars *vars, char **split_strs, int down);

// img_gestor.c (4/5)
void			file_to_image(t_vars *vars);
void			file_to_image_player(t_vars *vars);
char			*check_img_to_print(int map_value, t_vars *vars);
void			destroy_images(t_vars *vars);

// game_messages.c (5/5)
void			exit_message(void);
void			winner_message(void);
int				handle_invalid_file_error(void);
int				handle_argument_error(void);
int				is_valid_file_type(char *filename);

// check_path.c (5/5)
void			scan_player(t_vars *vars, char **str_to_path);
void			move_on_paths(int x, int y, char **map_copy, t_vars *vars);
void			check_valid_path(t_vars *vars);
void			scan_exit(t_vars *vars, char **str_to_path);
void			draw_exit_open(t_vars *vars);

// copi_split.c (3/5)
int				ft_split_size(char **split);
char			**ft_allocate_copy(int size);
char			**ft_copy_split(char **original);

// movements.c (5/5)
// static void	move_resume(t_vars *vars, int x, int y, int keycode);
void			move_up(t_vars *vars);
void			move_left(t_vars *vars);
void			move_down(t_vars *vars);
void			move_right(t_vars *vars);

#endif