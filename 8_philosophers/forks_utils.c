/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 11:49:16 by mzolotar          #+#    #+#             */
/*   Updated: 2025/05/13 12:12:00 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Updates the availability status of a fork.
 *
 * @param philo Pointer to the philosopher.
 * @param fork Index of the fork to update.
 * @param status New availability status (true or false).
 */

void	change_availability(t_philo *philo, int fork, bool status)
{
	pthread_mutex_lock(&philo->program->forks_lock);
	philo->program->forks_available[fork] = status;
	pthread_mutex_unlock(&philo->program->forks_lock);
}

/**
 * @brief Checks if a fork is currently available.
 *
 * @param philo Pointer to the philosopher.
 * @param fork Index of the fork to check.
 * @return true if the fork is available, false otherwise.
 */

bool	is_available(t_philo *philo, int fork)
{
	bool	available;

	pthread_mutex_lock(&philo->program->forks_lock);
	available = philo->program->forks_available[fork];
	pthread_mutex_unlock(&philo->program->forks_lock);
	return (available);
}

/**
 * @brief Handles fork release if philosopher dies during fork acquisition.
 *
 * @param philo Pointer to the philosopher.
 * @param fork1 Index of the first fork.
 * @param fork2 Index of the second fork.
 * @return true if philosopher is dead, false otherwise.
 */

bool	check_death_during_fork(t_philo *philo, int fork1, int fork2)
{
	if (!philosopher_dead(philo))
		return (false);
	if (philo->has_fork1)
		pthread_mutex_unlock(&philo->program->forks[fork1]);
	if (philo->has_fork2)
		pthread_mutex_unlock(&philo->program->forks[fork2]);
	pthread_mutex_lock(&philo->program->forks_lock);
	if (philo->has_fork1)
		philo->program->forks_available[fork1] = true;
	if (philo->has_fork2)
		philo->program->forks_available[fork2] = true;
	pthread_mutex_unlock(&philo->program->forks_lock);
	return (true);
}

/**
 * @brief Initializes fork possession flags for the philosopher.
 *
 * @param philo Pointer to the philosopher.
 */

void	init_fork_flags(t_philo *philo)
{
	philo->has_fork1 = false;
	philo->has_fork2 = false;
}

/**
 * @brief Releases forks held by the philosopher and updates availability.
 *
 * @param philo Pointer to the philosopher.
 */

void	free_forks(t_philo *philo)
{
	int	first;
	int	second;

	get_fork_order(philo, &first, &second);
	if (philo->has_fork2)
		pthread_mutex_unlock(&philo->program->forks[second]);
	if (philo->has_fork1)
		pthread_mutex_unlock(&philo->program->forks[first]);
	pthread_mutex_lock(&philo->program->forks_lock);
	if (philo->has_fork1)
		philo->program->forks_available[philo->id - 1] = true;
	if (philo->has_fork2)
		philo->program->forks_available[philo->id
			% philo->program->num_philos] = true;
	pthread_mutex_unlock(&philo->program->forks_lock);
	philo->has_fork1 = false;
	philo->has_fork2 = false;
}
