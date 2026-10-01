/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 09:32:11 by mzolotar          #+#    #+#             */
/*   Updated: 2025/05/13 12:25:06 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Attempts to take two forks in a specific order based on philosopher ID.
 *
 * @param philo Pointer to the philosopher.
 * @param left_fork Index of the left fork.
 * @param right_fork Index of the right fork.
 * @return true if forks are successfully taken, false otherwise.
 */

bool	take_two_forks(t_philo *philo, int left_fork, int right_fork)
{
	bool	fork_taken;

	if (philo->id % 2 != 0)
		fork_taken = take_forks(philo, left_fork, right_fork);
	else
	{
		usleep(20);
		fork_taken = take_forks(philo, right_fork, left_fork);
	}
	return (fork_taken);
}

/**
 * @brief Determines the order in which forks should be taken.
 *
 * @param philo Pointer to the philosopher.
 * @param first Pointer to store the first fork index.
 * @param second Pointer to store the second fork index.
 */

void	get_fork_order(t_philo *philo, int *first, int *second)
{
	int	fork1;
	int	fork2;

	fork1 = philo->id - 1;
	fork2 = philo->id % philo->program->num_philos;
	if (fork1 < fork2)
	{
		*first = fork1;
		*second = fork2;
	}
	else
	{
		*first = fork2;
		*second = fork1;
	}
}

/**
 * @brief Tries to take the first fork if it is available.
 *
 * @param philo Pointer to the philosopher.
 * @param first_fork Index of the first fork to take.
 */

void	try_take_first_fork(t_philo *philo, int first_fork)
{
	if (philo->has_fork1)
		return ;
	if (is_available(philo, first_fork))
	{
		change_availability(philo, first_fork, false);
		pthread_mutex_lock(&philo->program->forks[first_fork]);
		print_action(philo, TAKE_FORK);
		philo->has_fork1 = true;
	}
}

/**
 * @brief Attempts to take the second fork if it is available.
 *
 * @param philo Pointer to the philosopher.
 * @param second_fork Index of the second fork to take.
 * @return true if the fork is successfully taken, false otherwise.
 */

bool	try_take_second_fork(t_philo *philo, int second_fork)
{
	if (is_available(philo, second_fork))
	{
		change_availability(philo, second_fork, false);
		pthread_mutex_lock(&philo->program->forks[second_fork]);
		print_action(philo, TAKE_FORK);
		philo->has_fork2 = true;
		return (true);
	}
	return (false);
}

/**
 * @brief Attempts to take both forks using deadlock-avoiding order.
 *
 * @param philo Pointer to the philosopher.
 * @param fork1 Index of the first fork.
 * @param fork2 Index of the second fork.
 * @return true if both forks are successfully taken, false otherwise.
 */

bool	take_forks(t_philo *philo, int fork1, int fork2)
{
	int	first_fork;
	int	second_fork;

	get_fork_order(philo, &first_fork, &second_fork);
	init_fork_flags(philo);
	while (1)
	{
		if (check_death_during_fork(philo, fork1, fork2))
			return (false);
		try_take_first_fork(philo, first_fork);
		if (philo->has_fork1)
			if (try_take_second_fork(philo, second_fork))
				return (true);
	}
}
