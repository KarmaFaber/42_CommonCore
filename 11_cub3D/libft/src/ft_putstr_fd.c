/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isalazar <isalazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 01:28:49 by isalazar          #+#    #+#             */
/*   Updated: 2024/10/01 22:05:45 by isalazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"
#include <stdio.h>

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = write (fd, s, ft_strlen(s));
	i = i + 1;
}
