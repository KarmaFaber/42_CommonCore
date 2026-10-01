/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_map.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdiaz-he <jdiaz-he@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 00:18:13 by jdiaz-he          #+#    #+#             */
/*   Updated: 2025/06/08 12:59:01 by jdiaz-he         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

//falta revisar si asignar -1 a player_x, player_y y player_dir
t_map	*new_tmap(void)
{
	t_map	*map;

	map = (t_map *)ft_calloc(1, sizeof(t_map));
	if (!map)
	{
		print_malloc_error(__FILE__, __LINE__);
		return (NULL);
	}
	return (map);
}

void	init_tmap(t_map *map)
{
	if (!map)
		return ;
	map->map_str = NULL;
	map->rows = 0;
	map->cols = 0;
	map->p_total = 0;
	map->player_x = -1;
	map->player_y = -1;
	map->player_dir = -1;
}

// Set to NULL to avoid double free
void	free_tmap(t_map *map)
{
	if (!map)
		return ;
	ft_matrix_free(map->map_str);
	free(map);
	map = NULL;
}

void	free_exit_tmap(t_map *map, int status)
{
	free_tmap(map);
	exit(status);
}
