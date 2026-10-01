/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cubfile.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 18:34:56 by jdiaz-he          #+#    #+#             */
/*   Updated: 2025/08/06 20:47:46 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

/*
** Validates the .cub file by checking mandatory elements (textures,
** colors) and identifying the map section. It ensures all required
** components are present and correctly formatted.
**
** @param	t_cubfile *file	Pointer to the t_cubfile structure.
** @return	int 0 on success, 1 on failure (invalid or missing elements).
*/
int	check_cub(t_cubfile *file)
{
	int	i;

	i = 0;
	file->n_lines = 0;
	while (file->cub_str && file->cub_str[i])
	{
		if (empty_line(file->cub_str[i]))
		{
			i++;
			continue ;
		}
		if (check_cub_elements(file, file->cub_str[i]))
			return (set_error_msg(&file->error_msg, ft_itoa(i + 1)), 1);
		file->n_lines++;
		i++;
		if (file->texture_ea && file->texture_no
			&& file->texture_so && file->texture_we
			&& file->c_floor.filled && file->c_ceiling.filled)
			break ;
	}
	while (file->cub_str && file->cub_str[i] && empty_line(file->cub_str[i]))
		i++;
	if (file->n_lines != 6 || check_textures_files(file) || save_map(file, i))
		return (1);
	return (0);
}

/*
** Checks and parses a single line from the .cub file, identifying elements
** and storing texture paths and color definitions. It ensures that each
** required element (NO, SO, WE, EA, F, C) is only defined once.
**
** @param	t_cubfile *file	Pointer to the t_cubfile structure.
** @param	char *line	Line from the .cub file to be checked and parsed
** @return	int	0 on success, 1 on failure (invalid or duplicate element)
*/
int	check_cub_elements(t_cubfile *file, char *line)
{
	int	i;
	int	r;

	i = 0;
	r = 0;
	while (line[i] && line[i] <= 32)
		i++;
	if (ft_strncmp(&line[i], "NO ", 3) == 0 && !file->texture_no)
		file->texture_no = add_cub_texture(file, &line[i + 3]);
	else if (ft_strncmp(&line[i], "SO ", 3) == 0 && !file->texture_so)
		file->texture_so = add_cub_texture(file, &line[i + 3]);
	else if (ft_strncmp(&line[i], "WE ", 3) == 0 && !file->texture_we)
		file->texture_we = add_cub_texture(file, &line[i + 3]);
	else if (ft_strncmp(&line[i], "EA ", 3) == 0 && !file->texture_ea)
		file->texture_ea = add_cub_texture(file, &line[i + 3]);
	else if (ft_strncmp(&line[i], "F ", 2) == 0 && !file->c_floor.filled)
		r += add_cub_color(file, &file->c_floor, &line[i + 2]);
	else if (ft_strncmp(&line[i], "C ", 2) == 0 && !file->c_ceiling.filled)
		r += add_cub_color(file, &file->c_ceiling, &line[i + 2]);
	else
	{
		file->error_msg = ft_strdup("Check the .cub file at line <= ");
		r += 1;
	}
	return (r);
}

/*
** Checks if the texture files specified in the .cub file exist and are
** accessible. It also closes any successfully opened fd before returning.
**
** @param	t_cubfile *file	Pointer to the t_cubfile structure.
** @return	int	0 if all texture files are valid, 1 if any file is invalid
*/
int	check_textures_files(t_cubfile *file)
{
	int	fd[4];

	fd[NORTH] = open(file->texture_no, O_RDONLY);
	fd[SOUTH] = open(file->texture_so, O_RDONLY);
	fd[WEST] = open(file->texture_we, O_RDONLY);
	fd[EAST] = open(file->texture_ea, O_RDONLY);
	if (fd[NORTH] >= 0)
		close(fd[NORTH]);
	if (fd[SOUTH] >= 0)
		close(fd[SOUTH]);
	if (fd[WEST] >= 0)
		close(fd[WEST]);
	if (fd[EAST] >= 0)
		close(fd[EAST]);
	if (fd[NORTH] < 0 || fd[SOUTH] < 0 || fd[WEST] < 0 || fd[EAST] < 0)
	{
		file->error_msg = ft_strdup(ERR_TEXTURES ERR_PATH);
		return (1);
	}
	return (0);
}
