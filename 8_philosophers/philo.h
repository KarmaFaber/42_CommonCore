/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 11:08:11 by mzolotar          #+#    #+#             */
/*   Updated: 2025/05/13 12:27:45 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

//#➵⤐──╌╌➣⋆➣╌╌──⤏➵•➵⤐──╌╌➣⋆➣╌╌──includes:──╌╌➣⋆➣╌╌──⤏➵•➵⤐──╌╌➣⋆➣╌╌➔#

# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

//#➵⤐──╌╌➣⋆➣╌╌──⤏➵•➵⤐──╌╌➣⋆➣╌╌──Macros  :──╌╌➣⋆➣╌╌──⤏➵•➵⤐──╌╌➣⋆➣╌╌➔#

# define MAX_PHILOS 200
# define STR_MAX_PHILOS "200"

//#➵⤐──╌╌➣➣╌╌──ERR. MSGS:  :──╌╌➣➣╌╌➔#

# define STR_ERR_INPUT_DIGIT \
	"\001\033[1;31m\002Error: invalid input \
(not a valid unsigned integer between 0 and 2147483647).\n\001\033[0m\002"
# define STR_ERR_ARG \
	"\001\033[1;31m\002Error: incorrect number of arguments.\n\001\033[0m\002"
# define STR_ERR_P_NUM \
	"\001\033[1;31m\002Error:\
	 incorrect number of philosophers.\n\001\033[0m\002"
# define STR_ERR_INP \
	"\001\033[1;31m\002Error: incorrect input.\n\001\033[0m\002"
# define STR_ERR_THREAD \
	"\001\033[1;31m\002Error: Could not create thread.\n\001\033[0m\002"
# define STR_ERR_MALLOC \
	"\001\033[1;31m\002Error: Could not allocate memory.\n\001\033[0m\002"
# define STR_ERR_MUTEX \
	"\001\033[1;31m\002Error: Could not create mutex.\n\001\033[0m\002"

//#➵⤐─╌╌➣➣╌╌──PHILO. MSGS:  :─╌➣➣╌╌➔#
# define TAKE_FORK "has taken a fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define DIE "\001\033[1;31m\002died\001\033[0m\002"

//#➵⤐──╌╌➣⋆➣╌─⤏➵•➵⤐──╌╌➣⋆➣╌╌──Structures  :──╌╌➣⋆➣╌╌⤏➵•➵⤐──╌╌➣⋆➣╌╌➔#

typedef struct s_program
{
	unsigned short int	num_philos;
	unsigned int		num_times_to_eat;
	int					dead_p_num;
	bool				*forks_available;
	time_t				start_time;
	time_t				time_to_die;
	time_t				time_to_eat;
	time_t				time_to_sleep;
	pthread_mutex_t		forks_lock;
	pthread_mutex_t		*forks;
	pthread_mutex_t		write_lock;
	pthread_mutex_t		dead_num_lock;
	struct s_philo		*philos;
}						t_program;

typedef struct s_philo
{
	unsigned short int	id;
	unsigned int		meals_eaten;
	bool				has_fork1;
	bool				has_fork2;
	time_t				last_meal;
	pthread_t			thread;
	t_program			*program;

}						t_philo;

//#➵⤐╌╌➣⋆➣╌─⤏➵•➵⤐╌╌➣⋆➣╌╌─Function Prototypes : :──➣⋆➣╌⤏➵•➵⤐╌╌➣⋆➣╌╌➔#
// main.c
// int main (int argc, char **argv);

// parce.c
// static bool contain_digits_only(char *str);
int						atol_unsigned(const char *nptr);
bool					check_argvs(int argc_var, char **argv_var);

// init.c
// static int sub_init_program(t_program *program, char **argv);
int						init_program(t_program *program, char **argv);
void					handle_single_philosopher(t_philo *philo);
void					*philosopher_routine(void *arg);
int						init_philo(t_program *program);

// forks.c
bool					take_two_forks(t_philo *philo, int left_fork,
							int right_fork);
void					get_fork_order(t_philo *philo, int *first, int *second);
void					try_take_first_fork(t_philo *philo, int first_fork);
bool					try_take_second_fork(t_philo *philo, int second_fork);
bool					take_forks(t_philo *philo, int fork1, int fork2);

// forks_utils.c
void					change_availability(t_philo *philo, int fork,
							bool status);
bool					is_available(t_philo *philo, int fork);
bool					check_death_during_fork(t_philo *philo, int fork1,
							int fork2);
void					init_fork_flags(t_philo *philo);
void					free_forks(t_philo *philo);

// routines.c
bool					philosopher_dead(t_philo *philo);
bool					take_forks_and_eat(t_philo *philo, int left_fork,
							int right_fork);
bool					think_routine(t_philo *philo);
bool					sleep_routine(t_philo *philo);
void					all_routines(t_philo *philo, int left_fork,
							int right_fork);

// exit.c
void					free_all(t_program *program);
void					clean_pthreads(t_program *program, int created_threads);

// utils
long long				timestamp(void);
void					print_action(t_philo *philo, const char *action);
void					print_dead(t_philo *philo, const char *action);
void					precise_sleep(t_philo *philo, long long duration);
void					final_print(t_program *program);

#endif