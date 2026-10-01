/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_rotate_command.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 20:22:56 by mzolotar          #+#    #+#             */
/*   Updated: 2025/01/28 10:47:03 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/**
 * @brief Reverses a stack by moving the last node to the front of the stack.
 *
 * @param list Pointer to the stack list to perform the reverse rotation.
 * @return Void.
 */

static void	reverse_rotate(t_stack_list **list)
{
	t_stack_list	*last;
	int				size;

	size = list_size(*list);
	if (*list == NULL || list == NULL || size == 1)
		return ;
	last = find_last_node(*list);
	last->prev->next = NULL;
	last->next = *list;
	last->prev = NULL;
	*list = last;
	last->next->prev = last;
}

/**
 * @brief Reverse rotates stack 'a', moving its last node to the front,
	prints "rra".
 *
 * @param a Pointer to stack 'a' to apply the reverse rotation.
 * @return Void.
 */

void	rra(t_stack_list **a)
{
	reverse_rotate(a);
	write(1, "rra\n", 4);
}

/**
 * @brief Reverse rotates stack 'b', moving its last node to the front,
	prints "rrb".
 *
 * @param b Pointer to stack 'b' to apply the reverse rotation.
 * @return Void.
 */

void	rrb(t_stack_list **b)
{
	reverse_rotate(b);
	write(1, "rrb\n", 4);
}
/**
 * @brief Reverse rotates both stacks 'a' and 'b', prints "rrr".
 *
 * @param a Pointer to stack 'a' to apply the reverse rotation.
 * @param b Pointer to stack 'b' to apply the reverse rotation.
 * @return Void.
 */

void	rrr(t_stack_list **a, t_stack_list **b)
{
	reverse_rotate(a);
	reverse_rotate(b);
	write(1, "rrr\n", 4);
}
