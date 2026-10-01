/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdiaz-he <jdiaz-he@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 00:27:15 by jdiaz-he          #+#    #+#             */
/*   Updated: 2025/06/07 10:41:33 by jdiaz-he         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

/*
** Checks and validates command-line arguments.
**
** @param	int argc		Number of command-line arguments.
** @param	char **argv		Array of command-line argument strings.
** @param	t_cubfile *file	Pointer to the t_cubfile structure.
** @return	int				Return 1 on error, 0 on success.
*/
int	check_args(int argc, char **argv, t_cubfile *file)
{
	if (argc != 2)
	{
		file->error_msg = ft_strdup(ERR_N_ARGS);
		return (1);
	}
	if (check_cub_ext(argv[1]))
	{
		file->error_msg = ft_strdup(ERR_CUB);
		return (1);
	}
	file->fd = open(argv[1], O_RDONLY);
	if (file->fd < 1)
	{
		file->error_msg = ft_strdup(ERR_FILE ERR_PATH);
		return (1);
	}
	return (0);
}

/*
** Checks filemap extension ".cub"
**
** @param	char *file		The filename.
** @return	int				Return 1 on error, 0 on success.
*/
int	check_cub_ext(char *file)
{
	int	f;

	f = 0;
	while (file[f])
		f++;
	if (f < 4)
		return (1);
	if (file[--f] != 'b'
		|| file[--f] != 'u'
		|| file[--f] != 'c'
		|| file[--f] != '.')
		return (1);
	return (0);
}
