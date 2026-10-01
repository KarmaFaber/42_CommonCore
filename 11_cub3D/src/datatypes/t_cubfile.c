/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_cubfile.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdiaz-he <jdiaz-he@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 10:30:07 by jdiaz-he          #+#    #+#             */
/*   Updated: 2025/06/07 12:13:31 by jdiaz-he         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

t_cubfile	*new_tcubfile(void)
{
	t_cubfile	*file;

	file = (t_cubfile *)ft_calloc(1, sizeof(t_cubfile));
	if (!file)
	{
		print_malloc_error(__FILE__, __LINE__);
		return (NULL);
	}
	return (file);
}

void	init_tcubfile(t_cubfile *file)
{
	if (!file)
		return ;
	file->fd = -1;
	file->n_lines = 0;
	file->error_msg = NULL;
	file->cub_str = NULL;
	file->line = NULL;
	file->texture_no = NULL;
	file->texture_so = NULL;
	file->texture_we = NULL;
	file->texture_ea = NULL;
	init_tcolor(&file->c_floor);
	init_tcolor(&file->c_ceiling);
	file->map = new_tmap();
	if (!file->map)
		return ;
	init_tmap(file->map);
}

//file->map is freed in free_tgame
void	free_tcubfile(t_cubfile *file)
{
	if (!file)
		return ;
	if (file->fd > 0)
		close(file->fd);
	free(file->error_msg);
	ft_matrix_free(file->cub_str);
	free(file->line);
	free(file->texture_no);
	free(file->texture_so);
	free(file->texture_we);
	free(file->texture_ea);
	free(file);
}

void	free_exit_tcubfile(t_cubfile *file, int status)
{
	free_tcubfile(file);
	exit(status);
}
