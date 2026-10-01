/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd_int.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 09:57:14 by mzolotar          #+#    #+#             */
/*   Updated: 2024/10/14 09:59:53 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putstr_fd_int(char *s, int fd)
{
	if (!s)
		return (-1);
	if (fd == -1)
		return (-1);
	if (write(fd, s, ft_strlen(s)) == -1)
		return (-1);
	return (0);
}
