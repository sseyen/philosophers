/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisseye <alisseye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:37:03 by alisseye          #+#    #+#             */
/*   Updated: 2025/04/14 17:06:55 by alisseye         ###   ########.fr       */
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
}	t_sim;

typedef struct s_fork
{
	pthread_mutex_t	state_mutex;
	int				state;
}	t_fork;

typedef struct s_philo
{
	int				id;
	int				meals;
	pthread_t		thread;
	t_fork			*left_fork;
	t_fork			*right_fork;
	pthread_mutex_t	meal_mutex;
	struct timeval	last_meal;
	t_sim			*sim;
}	t_philo;

// Init
t_fork			*init_forks(t_sim *sim);
t_philo			*init_philos(t_sim *sim, t_fork *forks);

// Sim
void			set_simstate(t_sim *sim, int state);
int				get_simstate(t_sim *sim);
void			run_sim(t_sim *sim, t_philo *philos);
void			exit_sim(t_sim *sim, t_fork *forks, t_philo *philos);

// Philo
void			*philo_routine(void *arg);

// Utils philo
int				get_meals(t_philo *philo);
void			increase_meals(t_philo *philo);
int				get_last_meal(t_philo *philo);
int				set_last_meal(t_philo *philo);

// Fork
int				get_forkstate(t_fork *fork);
int				set_forkstate(t_philo *philo, t_fork *fork, int state);

// Utils numbers
int				ft_atoi(const char *str);
int				ft_isdigit(int c);
int				ft_isnumber(char *str);

// Utils
void			act(t_sim *sim, int ms);
int				timestamp(struct timeval *start);
void			mprintf(t_sim *sim, char *str, int timestamp, int id);

#endif