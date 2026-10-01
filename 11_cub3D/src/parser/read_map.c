/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 00:39:59 by jdiaz-he          #+#    #+#             */
/*   Updated: 2025/08/06 21:01:16 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

/*
** This function reads the map from the t_map structure and counts the
** number of players (N, S, E, W) in the map. It also updates the player's
** position (player_x, player_y) and the total number of players (p_total).
** It also keeps track of the maximum number of columns in the map.
**
** @param	t_game *game	Pointer to the t_game structure
** @param	t_map *map	Pointer to the t_map structure containing the map data
** @return	int			0 on success, 1 on failure (if map or map_str is NULL)
*/
int	read_map(t_game *game, t_map *map)
{
	int	i;
	int	j;

	i = -1;
	if (!map || !map->map_str)
		return (game->file->error_msg = ft_strdup(
				"Map or map_str is missing or empty.\nCheck " __FILE__"\n"), 1);
	while (map->map_str[++i])
	{
		j = -1;
		while (map->map_str[i][++j])
		{
			if (map->map_str[i][j] == 'N' || map->map_str[i][j] == 'S'
				|| map->map_str[i][j] == 'E' || map->map_str[i][j] == 'W')
			{
				game->map->p_total++;
				game->map->player_x = j;
				game->map->player_y = i;
				game->map->player_dir = map->map_str[i][j];
			}
		}
		if (map->cols < j)
			map->cols = j;
	}
	return (0);
}

/*
** This function checks if a line from the map section of the .cub file
** is valid. It ensures the line is not empty, not composed only of spaces
** or whitespace characters (such as tabs), and does not contain any
** character other than the allowed map symbols: '0', '1', 'N', 'S', 'W',
** 'E', or space.
**
** @param	t_cubfile *file		Pointer to the t_cubfile structure
** @param	char *line			Line from the .cub file to check
** @return	int					0 on success, 1 on failure (invalid line)
*/
int	check_line_map(t_cubfile *file, char *line)
{
	int		pos;
	char	*itoa_pos;

	pos = ft_strchrset(line, " 01NSEW");
	itoa_pos = ft_itoa(pos);
	if (empty_line(line) || !ft_strchrset(line, "\t\n\v\f\r "))
		return (file->error_msg = ft_strdup("Check the .cub file at line "),
			free(itoa_pos), 1);
	if (pos)
	{
		file->error_msg = ft_strdup("Check the .cub file at col ");
		file->error_msg = ft_strjoin_free(file->error_msg, ft_itoa(pos));
		file->error_msg = ft_strjoin_free(file->error_msg,
				ft_strdup(" in line "));
		return (free(itoa_pos), 1);
	}
	free(itoa_pos);
	return (0);
}

/*
** This function saves the map section from the .cub file into the map structure.
** It checks each line for validity, duplicates it, and dynamically expands the
** map array as needed. Updates the number of rows and maximum columns.
**
** @param	t_cubfile *file	Pointer to the t_cubfile structure
** @param	int i	Starting index of the map section in cub_str
** @return	int 0 on success, 1 on failure (memory allocation or invalid line)
*/
int	save_map(t_cubfile *file, int i)
{
	char	**tmp_str;
	int		j;
	int		t;

	j = 0;
	file->map->map_str = ft_calloc(2, sizeof(char *));
	if (!file->map->map_str)
		return (print_malloc_error(__FILE__, __LINE__), 1);
	while (file->cub_str[i])
	{
		if (check_line_map(file, file->cub_str[i]))
			return (set_error_msg(&file->error_msg, ft_itoa(i + 1)), 1);
		file->map->map_str[j++] = ft_strdup(file->cub_str[i++]);
		tmp_str = ft_calloc(j + 2, sizeof(char *));
		if (!tmp_str)
			return (print_malloc_error(__FILE__, __LINE__), 1);
		t = -1;
		while (file->map->map_str[++t])
			tmp_str[t] = file->map->map_str[t];
		free(file->map->map_str);
		file->map->map_str = tmp_str;
	}
	file->map->rows = j;
	return (0);
}
