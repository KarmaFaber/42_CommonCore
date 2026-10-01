/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 12:42:50 by mzolotar          #+#    #+#             */
/*   Updated: 2024/11/27 10:38:53 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/**
 * @brief Reads a single line from the given map file.
 *
 * @param fd File descriptor of the map file.
 * @return char* A pointer to the read line, or NULL on EOF.
 */

char	*read_map_line(int fd)
{
	return (get_next_line(fd));
}

/**
 * @brief Calculates the total size of the map in characters.
 *
 * @param vars Pointer to the game variables structure.
 * @return size_t Total size of the map in characters.
 */

size_t	ft_map_size(t_vars *vars)
{
	size_t	size;
	int		fd;
	char	*line;

	fd = open(vars->map_path, O_RDONLY);
	if (fd == -1)
	{
		ft_error(vars, "\033[1;31m🛑ERROR:\nError opening map file.\033[0m\n");
	}
	size = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		size += ft_strlen(line);
		free(line);
		line = NULL;
	}
	close(fd);
	return (size);
}

/**
 * @brief Calculates and sets the dimensions of the game window.
 *
 * @param vars Pointer to the game variables structure.
 * @return void
 */

void	fill_window_size(t_vars *vars)
{
	vars->win_width = XPM_SIZE * vars->y;
	vars->win_height = XPM_SIZE * vars->x;
	if (vars->win_height > MAX_HEIGHT_WIN)
	{
		ft_error(vars, "\033[1;31m🛑ERROR\nWindow height too large.\033[0m\n");
	}
	if (vars->win_width > MAX_WIDTH_WIN)
	{
		ft_error(vars, "\033[1;31m🛑ERROR:\nWindow width too large.\033[0m\n");
	}
}

/**
 * @brief Populates map-related variables like collectibles and size.
 *
 * @param str Pointer to the map string.
 * @param split_strs Array of strings split by rows.
 * @param vars Pointer to the game variables structure.
 * @return void
 */

void	ft_fill_map_vars(const char *str, char **split_strs, t_vars *vars)
{
	int	i;

	if (!str || !vars)
		return ;
	vars->c = ft_strchar_count(str, 'C');
	vars->p = ft_strchar_count(str, 'P');
	vars->e = ft_strchar_count(str, 'E');
	i = 0;
	while (split_strs[i] != NULL)
		i++;
	vars->x = i;
	if (i > 18)
	{
		ft_error(vars, "\033[1;31m🛑ERROR:\nSize of x > 18.\033[0m\n");
	}
	vars->y = ft_strlen(split_strs[0]);
	if (ft_strlen(split_strs[0]) > 32)
	{
		ft_error(vars, "\033[1;31m🛑ERROR:\nSize of y > 32.\033[0m\n");
	}
}
