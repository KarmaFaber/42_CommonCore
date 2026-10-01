/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 09:14:24 by mzolotar          #+#    #+#             */
/*   Updated: 2025/01/28 10:56:25 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/**
 * @brief Frees stack list and argv (if needed), prints error, and exits.
 *
 * @param list Pointer to the stack list to be freed.
 * @param argv Array of strings to free if argc_flag_2 is true.
 * @param argc_flag_2 Flag indicating if argv should be freed.
 * @return Void.
 */

void	error_exit(t_stack_list **list, char **argv, bool argc_flag_2)
{
	free_stack_list(list);
	if (argc_flag_2)
		free_split_argv(argv);
	write(2, "Error\n", 6);
	exit(1);
}

/**
 * @brief Frees a split argv array and its elements.
 *
 * @param argv Pointer to the array of strings to be freed.
 * @return Void.
 */

void	free_split_argv(char **argv)
{
	int	i;

	i = 0;
	if (argv == NULL || *argv == NULL)
		return ;
	while (argv[i])
	{
		free(argv[i]);
		i++;
	}
	free(argv);
}

/**
 * @brief Checks for syntax errors in a numeric string.
 *
 * @param argv_nbr String to validate as a numeric input.
 * @return 1 if there is a syntax error, 0 otherwise.
 */

int	error_syntax_argv(char *argv_nbr)
{
	if (!(*argv_nbr == '+' || *argv_nbr == '-' || (*argv_nbr >= '0'
				&& *argv_nbr <= '9')))
		return (1);
	if ((*argv_nbr == '+' || *argv_nbr == '-') && !(argv_nbr[1] >= '0'
			&& argv_nbr[1] <= '9'))
		return (1);
	while (*++argv_nbr)
	{
		if (!(*argv_nbr >= '0' && *argv_nbr <= '9'))
			return (1);
	}
	return (0);
}

/**
 * @brief Checks if a number already exists in the stack list.
 *
 * @param list Pointer to the stack list to search.
 * @param number Integer value to check for duplicates.
 * @return 1 if the number is found, 0 otherwise.
 */

int	error_repetition_int(t_stack_list *list, int number)
{
	if (list == NULL)
		return (0);
	while (list)
	{
		if (list->value == number)
			return (1);
		list = list->next;
	}
	return (0);
}

/**
 * @brief Frees all nodes in a stack list and sets the pointer to NULL.
 *
 * @param list Pointer to the stack list to be freed.
 * @return Void.
 */

void	free_stack_list(t_stack_list **list)
{
	t_stack_list	*temp;
	t_stack_list	*current;

	if (list == NULL)
		return ;
	current = *list;
	while (current)
	{
		temp = current->next;
		free(current);
		current = temp;
	}
	*list = NULL;
}
