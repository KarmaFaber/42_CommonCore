/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 20:20:06 by mzolotar          #+#    #+#             */
/*   Updated: 2025/01/28 12:42:07 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/**
 * @brief Swaps the first two nodes in a stack if the stack has at least two.
 *
 * @param list Pointer to the stack list to perform the swap.
 * @return Void.
 */

static void	swap(t_stack_list **list)
{
	t_stack_list	*first;
	t_stack_list	*second;

	if (*list == NULL || (*list)->next == NULL)
		return ;
	first = *list;
	second = first->next;
	first->next = second->next;
	if (second->next)
		second->next->prev = first;
	second->prev = NULL;
	second->next = first;
	first->prev = second;
	*list = second;
}

/**
 * @brief Performs the swap operation on stack 'a' and prints "sa".
 *
 * @param a Pointer to stack 'a' to apply the swap.
 * @return Void.
 */

void	sa(t_stack_list **a)
{
	swap(a);
	write(1, "sa\n", 3);
}

/**
 * @brief Performs the swap operation on stack 'b' and prints "sb".
 *
 * @param b Pointer to stack 'b' to apply the swap.
 * @return Void.
 */

void	sb(t_stack_list **b)
{
	swap(b);
	write(1, "sb\n", 3);
}

/**
 * @brief Performs the swap operation on both stacks 'a' and 'b', prints "ss".
 *
 * @param a Pointer to stack 'a' to apply the swap.
 * @param b Pointer to stack 'b' to apply the swap.
 * @return Void.
 */

void	ss(t_stack_list **a, t_stack_list **b)
{
	swap(a);
	swap(b);
	write(1, "ss\n", 3);
}
