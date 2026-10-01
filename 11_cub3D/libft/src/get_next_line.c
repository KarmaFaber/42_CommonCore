/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdiaz-he <jdiaz-he@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 14:01:18 by jdiaz-he          #+#    #+#             */
/*   Updated: 2025/03/04 10:13:54 by jdiaz-he         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

char	*ft_next_line_buffer(char *buffer)
{
	ssize_t	len;
	char	*line;

	if (!buffer || !*buffer)
		return (NULL);
	len = ft_strchr_index(buffer, ft_strlen_gnl(buffer), '\n');
	if (len < 0)
		return (NULL);
	line = ft_calloc(len + 2, sizeof(char));
	if (!line)
		return (NULL);
	len++;
	while (len--)
		line[len] = buffer[len];
	return (line);
}

char	*ft_next_buffer(char *buffer)
{
	ssize_t	i;
	size_t	j;
	char	*next_buffer;

	if (!buffer)
		return (NULL);
	i = ft_strchr_index(buffer, ft_strlen(buffer), '\n');
	if (i < 0)
		return (buffer);
	next_buffer = ft_calloc(ft_strlen(buffer) - i, sizeof(char));
	if (!next_buffer)
		return (NULL);
	j = 0;
	while (buffer[++i])
		next_buffer[j++] = buffer[i];
	free(buffer);
	return (next_buffer);
}

char	*ft_read_line_buffer(int fd)
{
	char	*line_buffer;
	ssize_t	r;

	line_buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!line_buffer)
		return (NULL);
	r = read(fd, line_buffer, BUFFER_SIZE);
	if (r <= 0)
	{
		free(line_buffer);
		return (NULL);
	}
	return (line_buffer);
}

char	*ft_gnl_by_buffer(int fd, char **buffer, char *line)
{
	char	*line_buffer;

	while (!line)
	{
		line = ft_next_line_buffer(*buffer);
		if (!line)
		{
			line_buffer = ft_read_line_buffer(fd);
			if (!line_buffer)
			{
				if (*buffer && **buffer)
					line = *buffer;
				else
					free(*buffer);
				*buffer = NULL;
				break ;
			}
			else
				*buffer = ft_strjoin_gnl(*buffer, line_buffer,
						*buffer, line_buffer);
		}
		else
			*buffer = ft_next_buffer(*buffer);
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*buff;
	char		*line;

	if (read(fd, 0, 0) < 0)
	{
		free(buff);
		buff = NULL;
		return (NULL);
	}
	line = NULL;
	line = ft_gnl_by_buffer(fd, &buff, line);
	return (line);
}
