/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 15:20:55 by mzolotar          #+#    #+#             */
/*   Updated: 2024/10/24 12:15:50 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/**
 * @brief Calculates the length of a string.
 * @param s The string to measure.
 * @return Length of the string.
 */

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

/**
 * @brief Duplicates a string by allocating memory.
 * @param s The string to duplicate.
 * @return Pointer to the newly allocated duplicate string.
 */

char	*ft_strdup(const char *s)
{
	size_t	i;
	char	*dup;

	dup = (char *)malloc(ft_strlen(s) + 1);
	if (!dup)
		return (NULL);
	i = 0;
	while (s[i])
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

/**
 * @brief Extracts a substring from a given string.
 *
 * @param s The original string.
 * @param start The starting index for the substring.
 * @param len The maximum length of the substring.
 * @return Pointer to the newly allocated substring
 * or NULL if start is beyond the end.
 */

char	*ft_strslice(const char *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	s_len;
	char	*substr;

	s_len = ft_strlen(s);
	if (start >= s_len)
		return (NULL);
	if (len > s_len - start)
		len = s_len - start;
	substr = (char *)malloc(len + 1);
	if (!substr)
		return (NULL);
	i = 0;
	while (i < len)
	{
		substr[i] = s[start + i];
		i++;
	}
	substr[len] = '\0';
	return (substr);
}

/**
 * @brief Joins two strings into a newly allocated string.
 * If 'line' is NULL, it will be treated as an empty string.
 * The function frees 'line' after appending 'temp'.
 *
 * @param line The first string (can be NULL),
	will be freed after the operation.
 * @param temp The second string to append.
 * @return Pointer to the newly allocated concatenated string.
 */

char	*ft_strappend(char *line, char *temp)
{
	size_t	i;
	size_t	j;
	char	*new_str;

	if (!line)
	{
		line = (char *)malloc(1 * sizeof(char));
		if (!line)
			return (NULL);
		line[0] = '\0';
	}
	new_str = malloc((ft_strlen(line) + ft_strlen(temp) + 1) * sizeof(char));
	if (!new_str)
		return (NULL);
	i = -1;
	j = 0;
	if (line)
		while (line[++i] != '\0')
			new_str[i] = line[i];
	while (temp[j] != '\0')
		new_str[i++] = temp[j++];
	new_str[ft_strlen(line) + ft_strlen(temp)] = '\0';
	free(line);
	return (new_str);
}

/**
 * @brief Finds the first occurrence of a character in a string.
 * @param s The string to search.
 * @param c The character to find.
 * @return Pointer to the first occurrence of the character, or NULL.
 */

char	*ft_strchr(char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	if (c == '\0')
		return ((char *)&s[ft_strlen(s)]);
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	return (0);
}
