/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   datatypes.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 00:32:20 by jdiaz-he          #+#    #+#             */
/*   Updated: 2025/08/11 08:23:07 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATATYPES_H
# define DATATYPES_H

/*** Typedefs ***/
typedef uint8_t	t_byte;

typedef struct s_color
{
	t_byte	red;
	t_byte	green;
	t_byte	blue;
	t_byte	filled;
}	t_color;

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_map
{
	char	**map_str;
	int		rows;
	int		cols;
	int		p_total;
	int		player_x;
	int		player_y;
	int		player_dir;
}	t_map;

typedef struct s_cubfile
{
	int		fd;
	int		n_lines;
	char	*error_msg;
	char	**cub_str;
	char	*line;
	char	*texture_no;
	char	*texture_so;
	char	*texture_ea;
	char	*texture_we;
	t_color	c_floor;
	t_color	c_ceiling;
	t_map	*map;
}	t_cubfile;

typedef struct s_img
{
	void	*img_ptr;
	char	*img_addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		img_width;
	int		img_height;
}	t_img;

typedef struct s_player
{
	double	pos_x_player;
	double	pos_y_player;
	double	dir_x_player;
	double	dir_y_player;
	double	plane_x_player;
	double	plane_y_player;
	double	move_speed;
	double	rot_speed;
}	t_player;

typedef struct s_ray
{
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	double	step;
	double	tex_pos;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		tex_x;
}	t_ray;

typedef struct s_game
{
	void		*mlx;
	void		*window;
	t_player	player;
	t_img		*screen;
	t_img		*textures[4];
	t_img		*img_struct;
	t_ray		*ray_struct;
	t_cubfile	*file;
	t_map		*map;
	char		*error_msg;
}	t_game;

/*** Prototypes ***/
//t_color.c
void		init_tcolor(t_color *color);

//t_cubfile.c
t_cubfile	*new_tcubfile(void);
void		init_tcubfile(t_cubfile *file);
void		free_tcubfile(t_cubfile *file);
void		free_exit_tcubfile(t_cubfile *file, int status);

//t_game.c
t_game		*new_tgame(void);
int			init_tgame(t_game *game);
int			init_tgame_visuals(t_game *game);
void		free_tgame(t_game *game);
void		free_exit_tgame(t_game *game, int status);

//t_img.c
t_img		*new_timg(void);
void		init_timg(t_img *img);
void		free_timg(t_img *img);
void		free_exit_timg(t_img *img, int status);

//t_map.c
t_map		*new_tmap(void);
void		init_tmap(t_map *map);
void		free_tmap(t_map *map);
void		free_exit_tmap(t_map *map, int status);

//t_player.c
void		init_tplayer(t_player *player);

//t_ray.c
t_ray		*new_tray(void);
void		init_tray(t_ray *ray);
void		free_tray(t_ray *ray);
void		free_exit_tray(t_ray *ray, int status);

#endif