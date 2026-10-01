/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 11:40:27 by mzolotar          #+#    #+#             */
/*   Updated: 2025/05/13 12:00:10 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Entry point of the philosopher program.
 *
 * @param argc Argument count from the command line.
 * @param argv Argument vector from the command line.
 * @return 0 on success, 1 on failure.
 */

int	main(int argc, char **argv)
{
	t_program	program;

	if (!check_argvs(argc, argv))
		return (1);
	if (!init_program(&program, argv) || !init_philo(&program))
		return (1);
	final_print(&program);
	free_all(&program);
	return (0);
}
