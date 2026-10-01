/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdiaz-he <jdiaz-he@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 18:26:25 by jdiaz-he          #+#    #+#             */
/*   Updated: 2024/04/17 11:57:47 by jdiaz-he         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

/**
*	Comprueba la longitud de una cadena.
*
*	No se comprueba si la cadena es null ya que la
*	original tampoco lo hace al estar marcada como
*	"non-null", por lo que salta un warning y provoca
*	un segfault si se ejecuta.
*
*	@param	str : Puntero a la cadena de caracteres.
*	@return	El tamaño de la cadena.
*/
size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
