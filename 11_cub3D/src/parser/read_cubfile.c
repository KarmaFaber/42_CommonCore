/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_cubfile.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 11:49:50 by jdiaz-he          #+#    #+#             */
/*   Updated: 2025/08/06 21:07:42 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static void	set_missing_elements(t_cubfile *file)
{
	if (!file->texture_no)
		file->error_msg = ft_strjoin_free(
				file->error_msg, ft_strdup(ERR_CUB_NO));
	if (!file->texture_so)
		file->error_msg = ft_strjoin_free(
				file->error_msg, ft_strdup(ERR_CUB_SO));
	if (!file->texture_ea)
		file->error_msg = ft_strjoin_free(
				file->error_msg, ft_strdup(ERR_CUB_EA));
	if (!file->texture_we)
		file->error_msg = ft_strjoin_free(
				file->error_msg, ft_strdup(ERR_CUB_WE));
	if (file->c_floor.filled == 0 && file->c_ceiling.filled == 0)
		file->error_msg = ft_strjoin_free(
				file->error_msg, ft_strdup(ERR_CUB_DUP));
	if (file->c_floor.filled == 0)
		file->error_msg = ft_strjoin_free(
				file->error_msg, ft_strdup(ERR_CUB_F));
	if (file->c_ceiling.filled == 0)
		file->error_msg = ft_strjoin_free(
				file->error_msg, ft_strdup(ERR_CUB_C));
}

/*
** This function reads the .cub file line by line, checking if the file
** is empty or if there are any errors during the loading process.
**
** @param	t_cubfile *file	Pointer to the t_cubfile structure
** @return	int	0 on success, 1 on failure (error in reading or loading)
*/
int	read_cubfile(t_cubfile *file)
{
	file->line = get_next_line(file->fd);
	if (!file->line)
	{
		file->error_msg = ft_strdup(ERR_CUB_EMPTY);
		return (1);
	}
	if (load_cubfile(file))
	{
		set_error_msg(&file->error_msg, ft_strdup(ERR_CUB_LOAD));
		return (1);
	}
	if (check_cub(file))
	{
		set_error_msg(&file->error_msg, ft_strdup(ERR_CUB_ITEMS));
		set_missing_elements(file);
		return (1);
	}
	return (0);
}

/*
** This function loads the content of the .cub file into memory.
** It reads each line, trims unnecessary characters, and dynamically
** expands the array to store all lines. The file descriptor is closed
** after reading, and the content is stored in the t_cubfile structure.
**
** @param	t_cubfile *file	Pointer to the t_cubfile structure
** @return	int				0 on success, 1 on failure (memory allocation error)
*/
int	load_cubfile(t_cubfile *file)
{
	char	**tmp_file;
	int		i;

	file->cub_str = ft_calloc(file->n_lines + 2, sizeof(char *));
	if (!file->cub_str)
		return (print_malloc_error(__FILE__, __LINE__), 1);
	while (file->line)
	{
		file->cub_str[file->n_lines] = ft_strdup_free(file->line);
		if (!file->cub_str[file->n_lines])
			return (print_malloc_error(__FILE__, __LINE__), 1);
		file->n_lines++;
		tmp_file = ft_calloc(file->n_lines + 2, sizeof(char *));
		if (!tmp_file)
			return (print_malloc_error(__FILE__, __LINE__), 1);
		i = -1;
		while (file->cub_str[++i])
			tmp_file[i] = file->cub_str[i];
		free(file->cub_str);
		file->cub_str = tmp_file;
		file->line = get_next_line(file->fd);
	}
	if (check_and_trim_load_cubfile(file) == 10)
		return (1);
	return (0);
}

/*
** This function checks the last character of the map to ensure it is not a
** newline ('\n'), indicating that the map ends properly without additional
** empty lines. It also trims newline characters from each line and frees the
** original memory.
**
** @param	t_cubfile *file	Pointer to the t_cubfile structure
** @return	int				The last character of the map (used for validation)
*/
int	check_and_trim_load_cubfile(t_cubfile *file)
{
	char	*for_free;
	int		i;
	int		end;

	i = 0;
	end = 0;
	while (file->cub_str && file->cub_str[i])
	{
		end = file->cub_str[i][ft_strlen(file->cub_str[i]) - 1];
		for_free = file->cub_str[i];
		file->cub_str[i] = ft_strtrim(file->cub_str[i], "\n");
		if (!file->cub_str[i])
			return (print_malloc_error(__FILE__, __LINE__), 10);
		free(for_free);
		i++;
	}
	if (end == '\n')
		file->error_msg = ft_strdup(
				"Map must be the last element in the file. \nChecks that the "
				"map exists and is the last element in the file.\nRemember: "
				"Nothing is allowed after the map, not even empty lines.\n");
	return (end);
}
