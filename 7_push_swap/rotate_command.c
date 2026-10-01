/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 20:22:29 by mzolotar          #+#    #+#             */
/*   Updated: 2025/01/28 10:46:10 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/**
 * @brief Rotates a stack by moving the first node to the end of the stack.
 *
 * @param list Pointer to the stack list to perform the rotation.
 * @return Void.
 */

static void	rotate(t_stack_list **list)
{
	t_stack_list	*last_node;
	int				size;

	size = list_size(*list);
	if (list == NULL || *list == NULL || size == 1)
		return ;
	last_node = find_last_node(*list);
	last_node->next = *list;
	*list = (*list)->next;
	(*list)->prev = NULL;
	last_node->next->prev = last_node;
	last_node->next->next = NULL;
}

/**
 * @brief Rotates stack 'a' by moving its first node to the end, prints "ra".
 *
 * @param a Pointer to stack 'a' to apply the rotation.
 * @return Void.
 */

void	ra(t_stack_list **a)
{
	rotate(a);
	write(1, "ra\n", 3);
}

/**
 * @brief Rotates stack 'b' by moving its first node to the end, prints "rb".
 *
 * @param b Pointer to stack 'b' to apply the rotation.
 * @return Void.
 */

void	rb(t_stack_list **b)
{
	rotate(b);
	write(1, "rb\n", 3);
}

/**
 * @brief Rotates both stacks 'a' and 'b' simultaneously, prints "rr".
 *
 * @param a Pointer to stack 'a' to apply the rotation.
 * @param b Pointer to stack 'b' to apply the rotation.
 * @return Void.
 */

void	rr(t_stack_list **a, t_stack_list **b)
{
	rotate(a);
	rotate(b);
	write(1, "rr\n", 3);
}
