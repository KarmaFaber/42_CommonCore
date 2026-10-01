/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubfile_elements.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdiaz-he <jdiaz-he@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 11:52:20 by jdiaz-he          #+#    #+#             */
/*   Updated: 2025/08/06 16:08:00 by jdiaz-he         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

/*
** Trims each RGB value in the array of strings if ALLOW_SPACES is set.
**
** @param	char **rgb		Array of strings containing RGB values.
** @return	char **			Final RGB trimmed array of strings.
*/
char	**rgb_trim(char **rgb)
{
	int		i;
	char	*trimmed;
	char	*set;

	if (!rgb)
		return (NULL);
	set = ALLOW_SPACES;
	i = 0;
	while (rgb[i])
	{
		trimmed = ft_strtrim(rgb[i], set);
		free(rgb[i]);
		rgb[i] = trimmed;
		i++;
	}
	return (rgb);
}

/*
** Adds a t_color data to the cubfile structure. This function trims the RGB
** values if ALLOW_SPACES is set, otherwise it checks for a valid RGB format
** without spaces. Only initial spaces are always ignored.
**
** @param	t_cubfile *file		Pointer to the t_cubfile structure.
** @param	t_color *color		Pointer to the t_color structure to fill.
** @param	char *line_chunk	The line chunk containing the RGB values.
** @return	int					0 on success, 1 on failure (invalid RGB format).
*/
int	add_cub_color(t_cubfile *file, t_color *color, char *line_chunk)
{
	char	**rgb;
	int		i;

	i = 0;
	while (line_chunk[i] && line_chunk[i] <= 32)
		i++;
	rgb = ft_split(&line_chunk[i], ',');
	if (ALLOW_SPACES)
		rgb = rgb_trim(rgb);
	if (!rgb || ft_matrix_size(rgb) != 3 || !ft_isnumeric(rgb[0], 1)
		|| !ft_isnumeric(rgb[1], 1) || !ft_isnumeric(rgb[2], 1))
	{
		file->error_msg = ft_strdup("Invalid RGB format. Expected three "
				"numeric values [0-255] separated by commas without spaces.\n"
				"Try with "CGRAY_DARK"make allow_spaces"CRED" if your file "
				"contains spaces or check the .cub file at line ");
		return (ft_matrix_free(rgb), 1);
	}
	if (check_color_values(rgb, file))
		return (ft_matrix_free(rgb), 1);
	color->red = ft_atoi(rgb[0]);
	color->green = ft_atoi(rgb[1]);
	color->blue = ft_atoi(rgb[2]);
	color->filled = 1;
	return (ft_matrix_free(rgb), 0);
}

int	check_color_values(char **rgb, t_cubfile *file)
{
	if (ft_atoi(rgb[0]) < 0 || ft_atoi(rgb[0]) > 255
		|| ft_atoi(rgb[1]) < 0 || ft_atoi(rgb[1]) > 255
		|| ft_atoi(rgb[2]) < 0 || ft_atoi(rgb[2]) > 255)
	{
		file->error_msg = ft_strdup("Invalid RGB VALUES. Expected three "
				"numeric values [0-255] separated by commas without spaces.\n"
				"Try with "CGRAY_DARK"make allow_spaces"CRED" if your file "
				"contains spaces or check the .cub file at line ");
		return (1);
	}
	return (0);
}

/*
** Adds a texture path to the cubfile structure. This function trims the path
** string if ALLOW_SPACES is set, otherwise it duplicates the string without
** initial spaces.
**
** @param	t_cubfile *file		Pointer to the t_cubfile structure.
** @param	char *line_chunk	The line chunk containing the texture path.
** @return	char *				The trimmed texture path.
*/
char	*add_cub_texture(t_cubfile *file, char *line_chunk)
{
	int		i;
	char	*trimmed_path;

	(void)file;
	i = 0;
	while (line_chunk[i] && line_chunk[i] <= 32)
		i++;
	if (ALLOW_SPACES)
		trimmed_path = ft_strtrim(&line_chunk[i], ALLOW_SPACES);
	else
		trimmed_path = ft_strdup(&line_chunk[i]);
	return (trimmed_path);
}
