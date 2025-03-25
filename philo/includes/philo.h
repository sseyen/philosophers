/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisseye <alisseye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:37:03 by alisseye          #+#    #+#             */
/*   Updated: 2025/03/25 22:55:08 by alisseye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_sim
{
	struct timeval	start;
	pthread_mutex_t	state_mutex;
	int				state;
	int				num_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_meals;
}	t_sim;

typedef struct s_fork
{
	pthread_mutex_t	mutex;
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
	struct timeval	last_meal;
	t_sim			*sim;
}	t_philo;

// Init
t_fork			*init_forks(t_sim *sim);
t_philo			*init_philos(t_sim *sim, t_fork *forks);

// Sim
int				set_simstate(t_sim *sim, int state);
int				get_simstate(t_sim *sim);
void			run_sim(t_sim *sim, t_philo *philos);

// Actions
void			die(t_philo *philo);
int				pick_fork(t_philo *philo, t_fork *first, t_fork *second);
int				eat(t_philo *philo);

// Fork
int				get_forkstate(t_fork *fork);
int				set_forkstate(t_philo *philo, t_fork *fork, int state);

// Utils
int				ft_atoi(const char *str);
int				ft_isdigit(int c);
int				ft_isnumber(char *str);
int				timestamp(struct timeval *start);
void			exit_sim(t_sim *sim, t_fork *forks, t_philo *philos);

#endif