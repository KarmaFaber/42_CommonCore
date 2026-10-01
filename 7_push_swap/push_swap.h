/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 09:34:40 by mzolotar          #+#    #+#             */
/*   Updated: 2025/01/28 18:36:46 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

//#➵⤐──╌╌➣⋆➣╌╌──⤏➵•➵⤐──╌╌➣⋆➣╌╌──includes:──╌╌➣⋆➣╌╌──⤏➵•➵⤐──╌╌➣⋆➣╌╌➔#

# include "libft/libft.h"
# include <limits.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdlib.h>

//#➵⤐──╌╌➣⋆➣╌╌──⤏➵•➵⤐──╌╌➣⋆➣╌╌───struct:──╌╌➣⋆➣╌─╌──⤏➵•➵⤐──╌╌➣⋆➣╌╌➔#

typedef struct s_stack_list
{
	int					value;
	int					index;
	int					push_cost;
	bool				above_median;
	bool				cheapest;
	struct s_stack_list	*target_node;
	struct s_stack_list	*next;
	struct s_stack_list	*prev;
}						t_stack_list;

/*#◉───▣───▢◇▢───▣───◉•◉───▣───▢Main:▢───▣───◉•◉───▣───▢◇▢───▣───◉#*/
// push_swap.c (2/5)
void					push_swap(t_stack_list **a, t_stack_list **b);
// int main (int argc, char **argv);

/*#◉───▣───▢◇▢───▣───◉•◉───▣───▢Errors:▢───▣───◉•◉───▣───▢◇▢───▣───◉#*/
// error_utils.c (5/5)
void					error_exit(t_stack_list **list, char **argv,
							bool argc_flag_2);
void					free_split_argv(char **argv);
int						error_syntax_argv(char *argv_nbr);
int						error_repetition_int(t_stack_list *list, int number);
void					free_stack_list(t_stack_list **list);

/*#◉──▢◇▢───◉•◉───▣───▢init and add: list_nodes.▢───▣───◉•◉────▢◇▢──◉#*/
// init_list_utils.c (3/5)
// static void	initialize_node(t_stack_list *node, int number);
void					add_node(t_stack_list **list, int number);
void					check_and_init_list(t_stack_list **a, char **argv,
							bool argc_flag_2);

/*#◉────▢◇▢───▣───◉•◉───▣───▢stack utils:▢───▣───◉•◉───▣───▢◇▢────◉#*/
// stack_utils.c (4/5)
t_stack_list			*find_last_node(t_stack_list *list);
t_stack_list			*find_smalles_value_list(t_stack_list *list);
t_stack_list			*find_biggest_value_list(t_stack_list *list);
int						list_size(t_stack_list *list);

/*#◉───▣───▢◇▢───▣───◉•◉───▣───▢Algotihtms:▢───▣───◉•◉───▣───▢◇▢───▣───◉#*/
// push_swap_utils.c (5/5)
void					rotate_both(t_stack_list **a, t_stack_list **b,
							t_stack_list *cheapest_node);
void					rev_rotate_both(t_stack_list **a, t_stack_list **b,
							t_stack_list *cheapest_node);
void					move_b_to_a(t_stack_list **a, t_stack_list **b);
void					move_a_to_b(t_stack_list **a, t_stack_list **b);
void					min_on_top(t_stack_list **a);

// algorithm_utils.c (5/5)
bool					check_stack_is_ordened(t_stack_list *list);
void					order_three(t_stack_list **list);
void					current_index_and_median(t_stack_list *list);
void					prep_for_push(t_stack_list **list,
							t_stack_list *top_node, char stack_name);
t_stack_list			*get_cheapest_node(t_stack_list *list);

// init_a_to_b.c (4/5)
// static void set_target_a(t_stack_list *a, t_stack_list *b);
// static void	cost_analysis_a(t_stack_list *a, t_stack_list *b);
void					set_cheapest(t_stack_list *list);
void					init_a_nodes_data(t_stack_list *a, t_stack_list *b);

// init_b_to_a.c (2/5)
// static void	set_target_b(t_stack_list *a, t_stack_list *b);
void					init_b_nodes_data(t_stack_list *a, t_stack_list *b);

/*#◉───▣───▢◇▢───▣───◉•◉───▣───▢Commands:▢───▣───◉•◉───▣───▢◇▢───▣───◉#*/
// swap_command.c (4/5)
// static void swap (t_stack_list **list);
void					sa(t_stack_list **a);
void					sb(t_stack_list **b);
void					ss(t_stack_list **a, t_stack_list **b);

// push_command.c (3/5)
// static void push (t_stack_list **dest, t_stack_list **src);
void					pa(t_stack_list **a, t_stack_list **b);
void					pb(t_stack_list **b, t_stack_list **a);

// rotate_command.c (4/5)
// static void	rotate(t_stack_list **list);
void					ra(t_stack_list **a);
void					rb(t_stack_list **b);
void					rr(t_stack_list **a, t_stack_list **b);

// reverse_rotate_comand.c (4/5)
// static void	reverse_rotate(t_stack_list **list);
void					rra(t_stack_list **a);
void					rrb(t_stack_list **b);
void					rrr(t_stack_list **a, t_stack_list **b);

#endif