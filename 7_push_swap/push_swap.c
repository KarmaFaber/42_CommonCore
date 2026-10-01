/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 09:34:44 by mzolotar          #+#    #+#             */
/*   Updated: 2025/01/28 13:54:15 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/**
 * @brief Sorts stack 'a' using auxiliary stack 'b' with push-swap logic.
 *
 * @param a Pointer to the stack 'a' list.
 * @param b Pointer to the stack 'b' list.
 * @return Void.
 */

void	push_swap(t_stack_list **a, t_stack_list **b)
{
	int	a_size;

	a_size = list_size(*a);
	if (a == NULL || *a == NULL || b == NULL)
		return ;
	if ((!check_stack_is_ordened(*a)) && (a_size-- > 3))
		pb(b, a);
	if ((!check_stack_is_ordened(*a)) && (a_size-- > 3))
		pb(b, a);
	while ((!check_stack_is_ordened(*a)) && (a_size-- > 3))
	{
		init_a_nodes_data(*a, *b);
		move_a_to_b(a, b);
	}
	order_three(a);
	while (*b)
	{
		init_b_nodes_data(*a, *b);
		move_b_to_a(a, b);
	}
	current_index_and_median(*a);
	min_on_top(a);
}

int	main(int argc, char **argv)
{
	t_stack_list	*a;
	t_stack_list	*b;

	a = NULL;
	b = NULL;
	if ((argc == 1) || (argc == 2 && !argv[1][0]))
		exit(EXIT_SUCCESS);
	else if (argc == 2)
		argv = ft_split(argv[1], ' ');
	if (argc == 2)
		check_and_init_list(&a, argv, true);
	else
		check_and_init_list(&a, argv + 1, false);
	if (!check_stack_is_ordened(a))
	{
		if (list_size(a) == 2)
			sa(&a);
		else if (list_size(a) == 3)
			order_three(&a);
		else
			push_swap(&a, &b);
	}
	free_stack_list(&a);
	return (0);
}
