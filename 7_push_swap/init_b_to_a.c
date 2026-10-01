/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_b_to_a.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 12:33:02 by mzolotar          #+#    #+#             */
/*   Updated: 2025/01/28 14:37:31 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/**
 * @brief Sets the target node for each element in list b based on list a.
 *
 * @param a The stack list a used to find target nodes for list b.
 * @param b The stack list b to set target nodes for.
 * @return None
 */

static void	set_target_b(t_stack_list *a, t_stack_list *b)
{
	t_stack_list	*current_a;
	t_stack_list	*target_node;
	long			best_match_index;

	while (b)
	{
		best_match_index = LONG_MAX;
		current_a = a;
		while (current_a)
		{
			if ((current_a->value > b->value)
				&& (current_a->value < best_match_index))
			{
				best_match_index = current_a->value;
				target_node = current_a;
			}
			current_a = current_a->next;
		}
		if (best_match_index == LONG_MAX)
			b->target_node = find_smalles_value_list(a);
		else
			b->target_node = target_node;
		b = b->next;
	}
}

/**
 * @brief Initializes data for nodes in list b and sets target nodes.
 *
 * @param a The stack list a used to find target nodes for list b.
 * @param b The stack list b to initialize.
 * @return None
 */

void	init_b_nodes_data(t_stack_list *a, t_stack_list *b)
{
	current_index_and_median(a);
	current_index_and_median(b);
	set_target_b(a, b);
}
