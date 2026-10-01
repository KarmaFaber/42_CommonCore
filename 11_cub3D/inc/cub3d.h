/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 00:05:25 by jdiaz-he          #+#    #+#             */
/*   Updated: 2025/08/06 20:51:12 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/*** Includes C ***/
# include <fcntl.h>
# include <unistd.h>
# include <stdint.h>
# include <limits.h>
# include <errno.h>
# include <stdio.h>
# include <string.h>
# include <sys/time.h>
# include <math.h>

/*** Includes cub3d ***/
# include "const.h"
# include "datatypes.h"
# include "game.h"

/*** MinilibX ***/
# include "../minilibx_linux/mlx.h"

/*** Includes libft ***/
# include "../libft/inc/libft.h"

/*** Prototypes ***/
//parser/check_args.c
int		check_args(int argc, char **argv, t_cubfile *file);
int		check_cub_ext(char *file);

//parser/check_cubfile.c
int		check_cub(t_cubfile *file);
int		check_cub_elements(t_cubfile *file, char *line);
int		check_textures_files(t_cubfile *file);

//paser/cubfile_elements.c
char	**rgb_trim(char **rgb);
int		add_cub_color(t_cubfile *file, t_color *color, char *line_chunk);
int		check_color_values(char **rgb, t_cubfile *file);
char	*add_cub_texture(t_cubfile *file, char *line_chunk);

//parser/utils.c
int		empty_line(char *line);
char	**map_str_copy(char **map_str, int height);
void	print_malloc_error(char *file, int line);
void	set_error_msg(char **error_msg, char *msg);
void	exit_unexpected(char *msg, char *file, int line, int code);

//parser/playable.c
char	*set_floodfill_error(int x, int y);
int		floodfill_stack(t_game *game, t_map *map, int start_x, int start_y);
int		floodfill_iterative(t_game *game, t_map *map, t_point *stack, int *top);
void	floodfill_adjust(t_map *map, t_point *stack, t_point *p, int *top);
int		map_playable(t_game *game, t_map *map);

//parser/read_cubfile.c
int		read_cubfile(t_cubfile *file);
int		load_cubfile(t_cubfile *file);
int		check_and_trim_load_cubfile(t_cubfile *file);

//parser/read_map.c
int		read_map(t_game *game, t_map *map);
int		check_line_map(t_cubfile *file, char *line);
int		save_map(t_cubfile *cub, int i);

#endif