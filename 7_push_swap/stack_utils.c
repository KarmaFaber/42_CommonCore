/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 10:30:39 by mzolotar          #+#    #+#             */
/*   Updated: 2025/01/28 10:49:55 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/**
 * @brief Finds the last node in a stack list.
 *
 * @param list Pointer to the stack list to search.
 * @return Pointer to the last node, or NULL if the list is empty.
 */

t_stack_list	*find_last_node(t_stack_list *list)
{
	if (list == NULL)
		return (NULL);
	while (list->next)
		list = list->next;
	return (list);
}

/**
 * @brief Finds the node with the smallest value in a stack list.
 *
 * @param list Pointer to the stack list to search.
 * @return Pointer to the smallest node, or NULL if the list is empty.
 */

t_stack_list	*find_smalles_value_list(t_stack_list *list)
{
	long			smallest;
	t_stack_list	*smallest_node;

	if (list == NULL)
		return (NULL);
	smallest = LONG_MAX;
	while (list)
	{
		if (list->value < smallest)
		{
			smallest = list->value;
			smallest_node = list;
		}
		list = list->next;
	}
	return (smallest_node);
}

/**
 * @brief Finds the node with the largest value in a stack list.
 *
 * @param list Pointer to the stack list to search.
 * @return Pointer to the largest node, or NULL if the list is empty.
 */

t_stack_list	*find_biggest_value_list(t_stack_list *list)
{
	long			biggest;
	t_stack_list	*biggest_node;

	if (list == NULL)
		return (NULL);
	biggest = LONG_MIN;
	while (list)
	{
		if (list->value > biggest)
		{
			biggest = list->value;
			biggest_node = list;
		}
		list = list->next;
	}
	return (biggest_node);
}

/**
 * @brief Counts the number of nodes in a stack list.
 *
 * @param list Pointer to the stack list to count nodes.
 * @return The total number of nodes in the list.
 */

int	list_size(t_stack_list *list)
{
	int	count;

	if (list == NULL)
		return (0);
	count = 0;
	while (list)
	{
		list = list->next;
		count++;
	}
	return (count);
}
