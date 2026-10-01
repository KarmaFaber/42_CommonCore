/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 13:38:33 by mzolotar          #+#    #+#             */
/*   Updated: 2025/05/13 12:24:37 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Returns the current timestamp in milliseconds.
 *
 * @param void
 * @return Current time in milliseconds since epoch.
 */

long long	timestamp(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

/**
 * @brief Prints a philosopher's action if no death has occurred.
 *
 * @param philo Pointer to the philosopher structure.
 * @param action String describing the action (e.g., "is eating").
 * @return void
 */

void	print_action(t_philo *philo, const char *action)
{
	pthread_mutex_lock(&philo->program->dead_num_lock);
	if (philo->program->dead_p_num > 0)
	{
		pthread_mutex_unlock(&philo->program->dead_num_lock);
		return ;
	}
	pthread_mutex_unlock(&philo->program->dead_num_lock);
	pthread_mutex_lock(&philo->program->write_lock);
	printf("%lld %hu %s\n", timestamp() - philo->program->start_time, philo->id,
		action);
	pthread_mutex_unlock(&philo->program->write_lock);
}

/**
 * @brief Prints the death message of a philosopher.
 *
 * @param philo Pointer to the philosopher structure.
 * @param action String describing the action (should be "died").
 * @return void
 */

void	print_dead(t_philo *philo, const char *action)
{
	pthread_mutex_lock(&philo->program->write_lock);
	printf("%lld %hu %s\n", timestamp() - philo->program->start_time, philo->id,
		action);
	pthread_mutex_unlock(&philo->program->write_lock);
}

/**
 * @brief Sleeps for a precise duration, interrupted if philosopher dies.
 *
 * @param philo Pointer to the philosopher structure.
 * @param duration Duration to sleep in milliseconds.
 * @return void
 */

void	precise_sleep(t_philo *philo, long long duration)
{
	long long	start;

	start = timestamp();
	while ((timestamp() - start) < duration)
	{
		if (philosopher_dead(philo))
			break ;
		usleep(10);
	}
}

/**
 * @brief Prints a final message if no philosopher has died.
 *
 * @param program Pointer to the main program structure.
 * @return void
 */

void	final_print(t_program *program)
{
	if (program->dead_p_num <= 0)
	{
		printf("\001\033[1;32m\002no one died today\n\001\033[0m\002");
	}
}
