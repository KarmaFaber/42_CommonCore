/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 10:31:57 by mzolotar          #+#    #+#             */
/*   Updated: 2024/11/27 10:39:40 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/**
 * @brief Processes a line and fills the map with the characters.
 *
 * @param line The line to be processed.
 * @param str_map The map to fill.
 * @param *index Pointer to the current index in the map.
 */

void	process_and_fill_map_line(char *line, char *str_map, size_t *index)
{
	size_t	j;

	j = 0;
	while (line[j])
	{
		if (line[j] == '\n')
			str_map[*index] = ' ';
		else
			str_map[*index] = line[j];
		(*index)++;
		j++;
	}
}

/**
 * @brief Reads and processes the map, filling the map array.
 *
 * @param fd The file descriptor for the map file.
 * @param str_map The map to be filled with data.
 */

void	ft_read_and_fill_map(int fd, char *str_map, t_vars *vars)
{
	char	*line;
	size_t	i;

	i = 0;
	line = read_map_line(fd);
	if (!line || ft_strlen(line) <= 1)
	{
		if (line)
			free(line);
		ft_error(vars, "\033[1;31m🛑ERROR:\nMap is empty.\033[0m\n");
	}
	while (line != NULL)
	{
		process_and_fill_map_line(line, str_map, &i);
		free(line);
		line = read_map_line(fd);
	}
}

/**
 * @brief Creates a string map by reading the map file and allocating memory.
 *
 * @param size Size of the map.
 * @param vars Pointer to the game variables structure.
 * @return char* Pointer to the created map string.
 */
char	*ft_create_str_map(size_t size, t_vars *vars)
{
	int		fd;
	char	*str_map;

	fd = open_map_file(vars);
	str_map = allocate_map_memory(size, vars);
	if (!str_map)
	{
		close(fd);
		return (NULL);
	}
	ft_read_and_fill_map(fd, str_map, vars);
	close(fd);
	verify_map_not_empty(str_map, vars);
	return (str_map);
}

/**
 * @brief Creates a map data structure with map string and split data.
 *
 * This function calculates the map size, creates the map string by
 * calling `ft_create_str_map`, and splits the map into rows using
 * `ft_split_map`. It returns the populated map data structure.
 *
 * @return t_map_data A map data structure with the map string and rows.
 */

t_map_data	ft_create_map_data(t_vars *vars, t_map_data *map_data)
{
	size_t	map_size_val;

	map_size_val = ft_map_size(vars);
	map_data->str_map = ft_create_str_map(map_size_val, vars);
	if (!map_data->str_map || ft_strlen(map_data->str_map) == 0)
	{
		ft_error(vars,
			"\033[1;31m🛑ERROR:\nMap is empty or couldn't be loaded.\033[0m\n");
	}
	map_data->split_strs = ft_split_map(map_data->str_map, vars);
	if (!map_data->split_strs)
	{
		free(map_data->str_map);
		ft_error(vars, "\033[1;31m🛑ERROR:\nFailed to split map.\033[0m\n");
	}
	return (*map_data);
}

/**
 * @brief Splits the map string into rows of characters.
 *
 * This function splits the provided map string by spaces and stores
 * each row as a separate string. It returns a pointer to an array of
 * strings representing the rows of the map.
 *
 * @param str_map The map string to be split.
 * @return char** An array of strings representing the split map rows.
 */

char	**ft_split_map(char const *str_map, t_vars *vars)
{
	char	**split_strs;

	split_strs = ft_split(str_map, ' ');
	if (!split_strs)
	{
		ft_error(vars,
			"\033[1;31m🛑ERROR:\nIt couldn't split str_map.\033[0m\n");
	}
	return (split_strs);
}
