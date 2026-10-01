/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 20:29:00 by mzolotar          #+#    #+#             */
/*   Updated: 2025/05/13 12:19:29 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Frees all allocated memory and destroys all mutexes in program.
 *
 * @param program Pointer to the main program structure to clean up.
 * @return void
 */

void	free_all(t_program *program)
{
	int	i;

	if (program->forks)
	{
		i = 0;
		while (i < program->num_philos)
		{
			pthread_mutex_destroy(&program->forks[i++]);
		}
		free(program->forks);
	}
	if (&program->write_lock)
		pthread_mutex_destroy(&program->write_lock);
	if (&program->dead_num_lock)
		pthread_mutex_destroy(&program->dead_num_lock);
	if (&program->forks_lock)
	{
		pthread_mutex_destroy(&program->forks_lock);
	}
	if (program->philos)
	{
		free(program->philos);
	}
	if (program->forks_available)
		free(program->forks_available);
}

/**
 * @brief Waits for all created philosopher threads and frees resources.
 *
 * @param program Pointer to the main program structure.
 * @param created_threads Number of threads successfully created.
 * @return void
 */

void	clean_pthreads(t_program *program, int created_threads)
{
	int	j;

	j = 0;
	printf("%s", STR_ERR_THREAD);
	while (j < created_threads)
	{
		pthread_join(program->philos[j].thread, NULL);
		j++;
	}
	free_all(program);
}
