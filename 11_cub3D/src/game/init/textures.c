/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdiaz-he <jdiaz-he@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 10:11:25 by mzolotar          #+#    #+#             */
/*   Updated: 2025/06/09 22:32:15 by jdiaz-he         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/cub3d.h"

void	check_file_to_image(t_img *tex, t_game *game, char *texture)
{
	if (!tex->img_ptr || !tex->img_addr)
	{
		ft_puterr(CRED"Error:\nFailed to load texture from file: ");
		ft_puterr(texture);
		ft_puterr(".\n");
		handle_exit(game, 1);
	}
	if (tex->img_width <= 0 || tex->img_height <= 0
		|| tex->img_width != XPM_SIZE || tex->img_height != XPM_SIZE)
	{
		ft_puterr(CRED"Error:\nInvalid texture dimensions for: ");
		ft_puterr(texture);
		ft_puterr(". Expected 64 x 64.\n");
		handle_exit(game, 1);
	}
}

/**
 * @brief Loads textures from XPM files and stores them in image structs.
 *
 * Uses MLX to convert texture file paths into usable image pointers and
 * stores metadata like width, height, and pixel data address.
 *
 * @param game Pointer to the main game structure.
 * @return void
 */
void	file_to_image(t_game *game)
{
	int		i;
	char	*textures[4];
	t_img	*tex;

	textures[NORTH] = game->file->texture_no;
	textures[SOUTH] = game->file->texture_so;
	textures[EAST] = game->file->texture_ea;
	textures[WEST] = game->file->texture_we;
	i = 0;
	while (i < 4)
	{
		tex = game->textures[i];
		tex->img_ptr = mlx_xpm_file_to_image(game->mlx,
				textures[i], &tex->img_width, &tex->img_height);
		if (tex->img_ptr)
			tex->img_addr = mlx_get_data_addr(tex->img_ptr,
					&tex->bits_per_pixel, &tex->line_length, &tex->endian);
		check_file_to_image(tex, game, textures[i]);
		i++;
	}
}
