/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 10:42:33 by mzolotar          #+#    #+#             */
/*   Updated: 2025/05/13 12:19:02 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Initializes basic fields and global mutexes in the program.
 *
 * @param program Pointer to the program structure to initialize.
 * @param argv Command-line arguments with simulation parameters.
 * @return 1 on success, 0 on failure.
 */

static int	sub_init_program(t_program *program, char **argv)
{
	program->dead_p_num = 0;
	program->num_philos = atol_unsigned(argv[1]);
	program->time_to_die = atol_unsigned(argv[2]);
	program->time_to_eat = atol_unsigned(argv[3]);
	program->time_to_sleep = atol_unsigned(argv[4]);
	if (argv[5])
		program->num_times_to_eat = atol_unsigned(argv[5]);
	else
		program->num_times_to_eat = -1;
	if (argv[5] && program->num_times_to_eat == 0)
		return (printf("%s", STR_ERR_INP), 0);
	if ((pthread_mutex_init(&program->write_lock, NULL) != 0)
		|| (pthread_mutex_init(&program->dead_num_lock, NULL) != 0)
		|| (pthread_mutex_init(&program->forks_lock, NULL) != 0))
		return (free_all(program), printf("%s", STR_ERR_MUTEX), 0);
	program->philos = malloc(sizeof(t_philo) * program->num_philos);
	if (!program->philos)
		return (free_all(program), printf("%s", STR_ERR_MALLOC), 0);
	return (1);
}

/**
 * @brief Initializes all program structures and resources.
 *
 * @param program Pointer to the main program structure.
 * @param argv Command-line arguments with configuration values.
 * @return 1 on success, 0 on error.
 */

int	init_program(t_program *program, char **argv)
{
	int	i;

	if (!sub_init_program(program, argv))
		return (0);
	program->forks = malloc(sizeof(pthread_mutex_t) * program->num_philos);
	if (!program->forks)
		return (free_all(program), printf("%s", STR_ERR_MALLOC), 0);
	i = 0;
	while (i < program->num_philos)
	{
		if (pthread_mutex_init(&program->forks[i], NULL) != 0)
			return (free_all(program), printf("%s", STR_ERR_MUTEX), 0);
		i++;
	}
	program->forks_available = malloc(sizeof(bool) * program->num_philos);
	if (!program->forks_available)
		return (free_all(program), printf("%s", STR_ERR_MALLOC), 0);
	i = 0;
	while (i < program->num_philos)
	{
		program->forks_available[i] = true;
		i++;
	}
	return (1);
}

/**
 * @brief Handles the special case of a single philosopher.
 *
 * @param philo Pointer to the philosopher structure.
 * @return void
 */

void	handle_single_philosopher(t_philo *philo)
{
	int	left_fork;

	left_fork = philo->id - 1;
	pthread_mutex_lock(&philo->program->forks[left_fork]);
	print_action(philo, TAKE_FORK);
	while (!philosopher_dead(philo))
		precise_sleep(philo, 1);
	pthread_mutex_unlock(&philo->program->forks[left_fork]);
}

/**
 * @brief Routine executed by each philosopher thread.
 *
 * @param arg Void pointer to the philosopher structure.
 * @return NULL always.
 */

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;
	int		left_fork;
	int		right_fork;

	philo = (t_philo *)arg;
	left_fork = philo->id - 1;
	right_fork = (philo->id) % philo->program->num_philos;
	if (philo->program->num_philos == 1)
	{
		handle_single_philosopher(philo);
		return (NULL);
	}
	all_routines(philo, left_fork, right_fork);
	return (NULL);
}

/**
 * @brief Initializes all philosophers and their threads.
 *
 * @param program Pointer to the program structure.
 * @return 1 on success, 0 if thread creation fails.
 */

int	init_philo(t_program *program)
{
	int	i;

	i = 0;
	program->start_time = timestamp();
	while (i < program->num_philos)
	{
		program->philos[i].id = i + 1;
		program->philos[i].meals_eaten = 0;
		program->philos[i].last_meal = timestamp();
		program->philos[i].program = program;
		if (pthread_create(&program->philos[i].thread, NULL,
				philosopher_routine, &program->philos[i]) != 0)
			return (free_all(program), clean_pthreads(program, i), 0);
		if (program->philos[i].id < 7)
			usleep(650);
		else
			usleep(300);
		i++;
	}
	if (program->num_philos % 2 != 0)
		usleep(100);
	i = 0;
	while (i < program->num_philos)
		pthread_join(program->philos[i++].thread, NULL);
	return (1);
}
