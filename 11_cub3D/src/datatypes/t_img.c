/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_img.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdiaz-he <jdiaz-he@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 00:23:15 by jdiaz-he          #+#    #+#             */
/*   Updated: 2025/06/08 12:58:09 by jdiaz-he         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

t_img	*new_timg(void)
{
	t_img	*img;

	img = (t_img *)ft_calloc(1, sizeof(t_img));
	if (!img)
	{
		print_malloc_error(__FILE__, __LINE__);
		return (NULL);
	}
	return (img);
}

// img_ptr and img_addr is filled in start_game_loop
void	init_timg(t_img *img)
{
	if (!img)
		return ;
	img->img_ptr = NULL;
	img->img_addr = NULL;
	img->bits_per_pixel = 0;
	img->line_length = 0;
	img->endian = 0;
	img->img_width = 0;
	img->img_height = 0;
}

// img_ptr and img_addr are managed and freed by the mlx library,
void	free_timg(t_img *img)
{
	if (!img)
		return ;
	free(img);
}

void	free_exit_timg(t_img *img, int status)
{
	free_timg(img);
	exit(status);
}
