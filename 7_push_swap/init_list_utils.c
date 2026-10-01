/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_list_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 09:57:11 by mzolotar          #+#    #+#             */
/*   Updated: 2025/01/28 10:41:36 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/**
 * @brief Initializes a stack node with default values and a given number.
 *
 * @param node Pointer to the node to be initialized.
 * @param number Integer value to assign to the node.
 * @return Void.
 */

static void	initialize_node(t_stack_list *node, int number)
{
	if (node == NULL)
		return ;
	node->value = number;
	node->index = -1;
	node->push_cost = 0;
	node->above_median = false;
	node->cheapest = false;
	node->target_node = NULL;
	node->next = NULL;
	node->prev = NULL;
}

/**
 * @brief Adds a new node with a given number to the end of a stack list.
 *
 * @param list Pointer to the stack list where the node will be added.
 * @param number Integer value to assign to the new node.
 * @return Void.
 */

void	add_node(t_stack_list **list, int number)
{
	t_stack_list	*node;
	t_stack_list	*last_node;

	if (list == NULL)
		return ;
	node = malloc(sizeof(t_stack_list));
	if (node == NULL)
		return ;
	initialize_node(node, number);
	if (*list == NULL)
		*list = node;
	else
	{
		last_node = find_last_node(*list);
		last_node->next = node;
		node->prev = last_node;
	}
}

/**
 * @brief Validates and initializes a stack list from a given argv array.
 *
 * @param a Pointer to the stack list to initialize.
 * @param argv Array of strings containing the input values.
 * @param argc_flag_2 Flag 🏁 to indicate if argv needs to be freed.
 * @return Void.
 */

void	check_and_init_list(t_stack_list **a, char **argv, bool argc_flag_2)
{
	long	number;
	int		i;

	i = 0;
	while (argv[i])
	{
		if (error_syntax_argv(argv[i]))
			error_exit(a, argv, argc_flag_2);
		number = ft_atol(argv[i]);
		if (number > INT_MAX || number < INT_MIN)
			error_exit(a, argv, argc_flag_2);
		if (error_repetition_int(*a, (int)number))
			error_exit(a, argv, argc_flag_2);
		add_node(a, (int)number);
		++i;
	}
	if (argc_flag_2)
		free_split_argv(argv);
}
