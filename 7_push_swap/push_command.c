/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 20:22:10 by mzolotar          #+#    #+#             */
/*   Updated: 2025/01/28 10:48:39 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/**
 * @brief Moves the top node from src stack to dest stack.
 * 🚨 If stack empty (i.e. NULL)
 * @param dest Pointer to the destination stack list.
 * @param src Pointer to the source stack list.
 * @return Void.
 */

static void	push(t_stack_list **dest, t_stack_list **src)
{
	t_stack_list	*node_to_push;

	if (!src || !*src)
	{
		return ;
	}
	node_to_push = *src;
	*src = (*src)->next;
	if (*src)
		(*src)->prev = NULL;
	node_to_push->prev = NULL;
	if (*dest == NULL)
	{
		*dest = node_to_push;
		node_to_push->next = NULL;
	}
	else
	{
		node_to_push->next = *dest;
		node_to_push->next->prev = node_to_push;
		*dest = node_to_push;
	}
}

/**
 * @brief Pushes the top node of stack 'b' to stack 'a' and prints "pa".
 *
 * @param a Pointer to stack 'a' to receive the node.
 * @param b Pointer to stack 'b' to provide the node.
 * @return Void.
 */

void	pa(t_stack_list **a, t_stack_list **b)
{
	push(a, b);
	write(1, "pa\n", 3);
}

/**
 * @brief Pushes the top node of stack 'a' to stack 'b' and prints "pb".
 *
 * @param b Pointer to stack 'b' to receive the node.
 * @param a Pointer to stack 'a' to provide the node.
 * @return Void.
 */

void	pb(t_stack_list **b, t_stack_list **a)
{
	push(b, a);
	write(1, "pb\n", 3);
}
