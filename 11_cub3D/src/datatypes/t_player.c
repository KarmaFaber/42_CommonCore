/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_player.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdiaz-he <jdiaz-he@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 00:24:15 by jdiaz-he          #+#    #+#             */
/*   Updated: 2025/06/08 12:59:18 by jdiaz-he         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

// move_speed recomendado: 0.05 to 0.15
// rot_speed recomendado: 0.03 to 0.07
// player->fov not exist for now, but it could be added later (value 60.0)
void	init_tplayer(t_player *player)
{
	if (!player)
	{
		print_malloc_error(__FILE__, __LINE__);
		return ;
	}
	player->pos_x_player = 0.0;
	player->pos_y_player = 0.0;
	player->dir_x_player = 0.0;
	player->dir_y_player = 0.0;
	player->plane_x_player = 0.0;
	player->plane_y_player = 0.0;
	player->move_speed = 0.12;
	player->rot_speed = 0.06;
}
