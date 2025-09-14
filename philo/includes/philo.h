/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisseye <alisseye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:37:03 by alisseye          #+#    #+#             */
/*   Updated: 2025/09/14 22:47:03 by alisseye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <string.h>

# define EATING "is eating"
# define SLEEPING "is sleeping"
# define THINKING "is thinking"
# define FORK_TAKEN "has taken a fork"
# define DEAD "died"

typedef struct s_sim
{
	struct timeval	start;
	pthread_mutex_t	state_mutex;
	int				state;
	pthread_mutex_t	print_mutex;
	int				num_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_meals;
	int				delay;
}	t_sim;

typedef struct s_philo
{
	int				id;
	int				meals;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	meal_mutex;
	struct timeval	last_meal;
	t_sim			*sim;
}	t_philo;

// Parse
int					parse_args(int argc, char **argv, t_sim *sim);

// Init
pthread_mutex_t		*init_forks(t_sim *sim);
t_philo				*init_philos(t_sim *sim, pthread_mutex_t *forks);

// Sim
void				set_simstate(t_sim *sim, int state);
int					get_simstate(t_sim *sim);
void				run_sim(t_sim *sim, t_philo *philos);
void				exit_sim(t_sim *sim, pthread_mutex_t *forks, \
					t_philo *philos);

// Philo
void				*philo_routine(void *arg);

// Utils philo
int					get_meals(t_philo *philo);
void				increase_meals(t_philo *philo);
int					get_last_meal(t_philo *philo);
int					set_last_meal(t_philo *philo);

// Utils
void				act(int ms);
int					timestamp(struct timeval *start);
void				print_status(t_sim *sim, struct timeval *time, \
					int id, char *status);

#endif