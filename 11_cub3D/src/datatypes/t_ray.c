/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_ray.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdiaz-he <jdiaz-he@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 00:29:49 by jdiaz-he          #+#    #+#             */
/*   Updated: 2025/06/08 12:59:25 by jdiaz-he         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

t_ray	*new_tray(void)
{
	t_ray	*ray;

	ray = (t_ray *)ft_calloc(1, sizeof(t_ray));
	if (!ray)
	{
		print_malloc_error(__FILE__, __LINE__);
		return (NULL);
	}
	return (ray);
}

void	init_tray(t_ray *ray)
{
	if (!ray)
		return ;
	ray->camera_x = 0.0;
	ray->ray_dir_x = 0.0;
	ray->ray_dir_y = 0.0;
	ray->side_dist_x = 0.0;
	ray->side_dist_y = 0.0;
	ray->delta_dist_x = 0.0;
	ray->delta_dist_y = 0.0;
	ray->perp_wall_dist = 0.0;
	ray->step = 0.0;
	ray->tex_pos = 0.0;
	ray->map_x = 0;
	ray->map_y = 0;
	ray->step_x = 0;
	ray->step_y = 0;
	ray->hit = 0;
	ray->side = 0;
	ray->line_height = 0;
	ray->draw_start = 0;
	ray->draw_end = 0;
	ray->tex_x = 0;
}

void	free_tray(t_ray *ray)
{
	if (!ray)
		return ;
	free(ray);
}

void	free_exit_tray(t_ray *ray, int status)
{
	free_tray(ray);
	exit(status);
}
