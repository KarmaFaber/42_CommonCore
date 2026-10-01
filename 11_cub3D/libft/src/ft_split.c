/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdiaz-he <jdiaz-he@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 09:33:12 by jdiaz-he          #+#    #+#             */
/*   Updated: 2025/02/21 10:03:59 by jdiaz-he         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

static size_t	ft_wordc(char const *s, char c)
{
	size_t	count;
	size_t	i;

	count = 0;
	i = 0;
	while (i < ft_strlen(s) && s[i])
	{
		if (s[i] != c)
		{
			count++;
			while (s[i] && s[i] != c)
				i++;
		}
		else
			i++;
	}
	return (count);
}

static void	*ft_free(char **split, int i)
{
	i--;
	if (!split)
		return (NULL);
	while (i >= 0 && split[i])
	{
		free(split[i]);
		i--;
	}
	free(split);
	return (NULL);
}

static char	*ft_splitword(char *s, char c, int *j)
{
	int		len;
	char	*word;
	int		i;

	i = *j;
	len = 0;
	while (s[*j] && s[*j] != c)
	{
		len++;
		(*j)++;
		i++;
	}
	word = ft_calloc(1, len + 1);
	if (!word)
		return (NULL);
	word[len] = '\0';
	len--;
	i--;
	while (len >= 0)
	{
		word[len--] = s[i--];
	}
	return (word);
}

static	char	**ft_splitgen(char **split, char *s, char c, size_t wordc)
{
	size_t	i;
	int		j;

	i = 0;
	j = 0;
	while (i < wordc)
	{
		if (s[j] && s[j] != c)
		{
			split[i] = ft_splitword(s, c, &j);
			if (!split[i])
				return (ft_free(split, i));
		}
		else
		{
			j++;
			i--;
		}
		i++;
	}
	split[i] = 0;
	return (split);
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	size_t	wordc;

	if (!s)
		return (0);
	wordc = ft_wordc(s, c);
	split = ft_calloc(wordc + 1, sizeof(char *));
	if (!split)
		return (0);
	split = ft_splitgen(split, (char *) s, c, wordc);
	return (split);
}
