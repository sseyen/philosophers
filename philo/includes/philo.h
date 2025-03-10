/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisseye <alisseye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:37:03 by alisseye          #+#    #+#             */
/*   Updated: 2025/03/10 18:00:45 by alisseye         ###   ########.fr       */
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
	pthread_mutex_t	all_alive_mutex;
	int				all_alive;
	int				num_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_meals;
}	t_sim;

typedef struct s_philo
{
	int				id;
	int				meals;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	struct timeval	last_meal;
	t_sim			*sim;
}	t_philo;

void			run_sim(t_sim *sim, t_philo *philos, pthread_mutex_t *forks);

// Init
pthread_mutex_t	*init_forks(t_sim *sim);
t_philo			*init_philos(t_sim *sim, pthread_mutex_t *forks);

// Utils
int				ft_atoi(const char *str);
int				ft_isdigit(int c);
int				ft_isnumber(char *str);
int				timestamp(struct timeval *start);
void			exit_sim(t_sim *sim, pthread_mutex_t *forks, t_philo *philos);

#endif