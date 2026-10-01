/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdiaz-he <jdiaz-he@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 14:38:54 by jdiaz-he          #+#    #+#             */
/*   Updated: 2024/04/15 20:34:29 by jdiaz-he         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
*	Comprueba si un caracter es un digito.
*	Version sin caracteres literales, comparando con el valor ASCII directamente.
*
*	@param	c : Caracter a comprobar.
*	@return	El valor del caracter comprobado si coincide o 0.
*/
int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (c);
	return (0);
}
