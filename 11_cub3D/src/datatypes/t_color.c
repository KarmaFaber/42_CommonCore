/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_color.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 13:46:33 by jdiaz-he          #+#    #+#             */
/*   Updated: 2025/08/07 09:24:54 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	init_tcolor(t_color *color)
{
	if (!color)
	{
		print_malloc_error(__FILE__, __LINE__);
		return ;
	}
	color->red = 0;
	color->green = 0;
	color->blue = 0;
	color->filled = 0;
}
