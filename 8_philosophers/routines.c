/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 19:36:20 by mzolotar          #+#    #+#             */
/*   Updated: 2025/05/13 12:13:32 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Checks if the philosopher is dead or has died from starvation.
 *
 * @param philo Pointer to the philosopher.
 * @return true if the philosopher is dead, false otherwise.
 */

bool	philosopher_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->program->dead_num_lock);
	if (philo->program->dead_p_num > 0)
	{
		pthread_mutex_unlock(&philo->program->dead_num_lock);
		return (true);
	}
	if (timestamp() - philo->last_meal >= philo->program->time_to_die)
	{
		philo->program->dead_p_num++;
		if (philo->program->dead_p_num == 1)
		{
			print_dead(philo, DIE);
		}
		pthread_mutex_unlock(&philo->program->dead_num_lock);
		return (true);
	}
	pthread_mutex_unlock(&philo->program->dead_num_lock);
	return (false);
}

/**
 * @brief Attempts to take forks and perform eating routine.
 *
 * @param philo Pointer to the philosopher.
 * @param left_fork Index of the left fork.
 * @param right_fork Index of the right fork.
 * @return true if the philosopher successfully eats, false otherwise.
 */

bool	take_forks_and_eat(t_philo *philo, int left_fork, int right_fork)
{
	precise_sleep(philo, 1);
	if (!take_forks(philo, left_fork, right_fork))
		return (false);
	precise_sleep(philo, 1);
	if (philosopher_dead(philo))
	{
		free_forks(philo);
		return (false);
	}
	philo->last_meal = timestamp();
	print_action(philo, EAT);
	precise_sleep(philo, philo->program->time_to_eat);
	philo->meals_eaten++;
	free_forks(philo);
	return (true);
}

/**
 * @brief Executes the thinking routine for a philosopher.
 *
 * @param philo Pointer to the philosopher.
 * @return true if the routine completes, false if philosopher is dead.
 */

bool	think_routine(t_philo *philo)
{
	precise_sleep(philo, 1);
	if (philosopher_dead(philo))
		return (false);
	print_action(philo, THINK);
	return (true);
}

/**
 * @brief Executes the sleeping routine for a philosopher.
 *
 * @param philo Pointer to the philosopher.
 * @return true if the routine completes, false if philosopher is dead.
 */

bool	sleep_routine(t_philo *philo)
{
	precise_sleep(philo, 1);
	if (philosopher_dead(philo))
	{
		return (false);
	}
	print_action(philo, SLEEP);
	precise_sleep(philo, philo->program->time_to_sleep);
	return (true);
}

/**
 * @brief Handles the philosopher's routine of thinking, eating, and sleeping.
 *
 * @param philo Pointer to the philosopher.
 * @param left_fork Index of the left fork.
 * @param right_fork Index of the right fork.
 */

void	all_routines(t_philo *philo, int left_fork, int right_fork)
{
	while ((!(philosopher_dead(philo)) && (philo->program->num_times_to_eat == 0
				|| philo->meals_eaten < philo->program->num_times_to_eat)))
	{
		if (!think_routine(philo))
			break ;
		if (!take_forks_and_eat(philo, left_fork, right_fork))
		{
			break ;
		}
		if (!sleep_routine(philo))
			break ;
	}
}
