/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdiaz-he <jdiaz-he@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 11:50:44 by jdiaz-he          #+#    #+#             */
/*   Updated: 2025/06/07 12:00:47 by jdiaz-he         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

/*
** Check if a line is empty. If ALLOW_SPACES is defined,
** it will also consider lines with only spaces as empty.
**
** @param	char *line		Line to check;
** @return	int				1 if the line is empty, 0 otherwise.
*/
int	empty_line(char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (0);
	if (ALLOW_SPACES)
		while (line[i] && ft_strchr(ALLOW_SPACES, line[i]))
			i++;
	while (line[i] && line[i] == 10)
		i++;
	if (line[i] == '\0')
		return (1);
	return (0);
}

/*
** Copy a map (char **map_str) of height elements (char *)
** to a new_map_str.
**
** @param	char **map_str	Char ** to copy;
** @param	int *height		N of elements (char *) in map_str;
** @return	char **			New map or NULL on error.
*/
char	**map_str_copy(char **map_str, int height)
{
	char	**new_map_str;

	if (!map_str)
		return (NULL);
	new_map_str = ft_calloc(height + 1, sizeof(char *));
	if (!new_map_str)
		return (NULL);
	new_map_str[height] = NULL;
	while (height)
	{
		new_map_str[height - 1] = ft_strdup(map_str[height - 1]);
		height--;
	}
	return (new_map_str);
}

/*
** Print an error message indicating that memory allocation failed.
** It includes the file name and line number where the error occurred.
**
** @param	char *file		Name of the file where the error occurred;
** @param	int line		Line number where the error occurred.
*/
void	print_malloc_error(char *file, int line)
{
	char	*line_str;

	line_str = ft_itoa(line);
	ft_puterr(CRED ERROR "Memory allocation failed at ");
	ft_puterr(file);
	ft_puterr(":");
	ft_puterr(line_str);
	ft_puterr(CRESET "\n");
	free(line_str);
}

/*
** Sets an error message in the provided error_msg pointer.
** If the new message is NULL, it does nothing.
** If error_msg already contains a message, it frees the previous memory
** and creates a new string with the combined messages.
** If the new message does not end with a newline, it appends ".\n"
**
** @param	char **error_msg	Pointer to the error message string
** @param	char *msg			Message to append to the error message
** @return	void
*/
void	set_error_msg(char **error_msg, char *msg)
{
	if (!msg)
		return ;
	if (*error_msg)
		*error_msg = ft_strjoin_sfree(
				*error_msg, msg,
				*error_msg, msg);
	else
		*error_msg = ft_strdup_free(msg);
	if (!*error_msg)
		print_malloc_error(__FILE__, __LINE__);
	if (*error_msg && (*error_msg)[ft_strlen(*error_msg) - 1] != '\n')
	{
		*error_msg = ft_strjoin_sfree(
				*error_msg, ".\n",
				*error_msg, NULL);
	}
}

/*
** Exits the program when an unexpected error occurs.
** It prints an error message with the provided message, file name, and line
** number, and then exits with the specified exit code.
**
** @param	char *msg		Message to print before exiting
** @param	char *file		Name of the file where the error occurred
** @param	int line		Line number where the error occurred
** @param	int code		Exit code to use when exiting the program
** @note				If msg is NULL, it defaults to "Unexpected exit"
*/
void	exit_unexpected(char *msg, char *file, int line, int code)
{
	char	*line_str;

	if (!msg)
		msg = "Unexpected exit";
	line_str = ft_itoa(line);
	ft_puterr(CRED ERROR);
	ft_puterr(msg);
	ft_puterr(" at ");
	ft_puterr(file);
	ft_puterr(":");
	ft_puterr(line_str);
	ft_puterr(CRESET "\n");
	free(line_str);
	exit(code);
}
