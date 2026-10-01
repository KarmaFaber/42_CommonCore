/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iter.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 13:17:21 by mzolotar          #+#    #+#             */
/*   Updated: 2025/11/07 11:10:30 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITER_HPP
#define ITER_HPP

#include <iostream>

template<typename T, typename T_func>
void iter(T *array, size_t arr_len, T_func my_func)
{
	if (array == NULL)
		return;
	for (size_t i = 0; i < arr_len; ++i)
		my_func(array[i]);
}

template<typename T, typename T_func>
void iter(const T *array, size_t arr_len, T_func my_func)
{
	if (array == NULL)
		return;
	for (size_t i = 0; i < arr_len; ++i)
		my_func(array[i]);
}

#endif
