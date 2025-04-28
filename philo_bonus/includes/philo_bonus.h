/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisseye <alisseye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 14:19:09 by alisseye          #+#    #+#             */
/*   Updated: 2025/04/28 13:37:53 by alisseye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <signal.h>
# include <sys/time.h>
# include <semaphore.h>

typedef struct s_sim
{
	sem_t			*print_sem;
	sem_t			*forks_sem;
	struct timeval	start_time;
	int				num_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_meals;
}	t_sim;

typedef struct s_philo
{
	int				id;
	pid_t			pid;
	int				meals;
	struct timeval	last_meal;
	sem_t			*meal_sem;
	t_sim			*sim;
}	t_philo;

// Parse
int				parse_args(int argc, char **argv, t_sim *sim);

// Init
int				init_sems(t_sim *sim, sem_t **forks);
int				init_philos(t_sim *sim, t_philo **philos);

// Sim
void			run_sim(t_sim *sim, t_philo *philos);

// Philo
int				philo_main(t_philo *philo, t_sim *sim);

// Utils philo
int				get_last_meal(t_philo *philo);
void			set_last_meal(t_philo *philo);
void			increase_meals(t_philo *philo);
int				get_num_meals(t_philo *philo);

// Utils
int				timestamp(struct timeval *start);
void			act(int ms);
void			exit_sim(t_sim *sim, sem_t *forks, t_philo *philos);
void			sprint(t_sim *sim, char *str, int timestamp, int id);

#endif