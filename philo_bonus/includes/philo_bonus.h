/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisseye <alisseye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 14:19:09 by alisseye          #+#    #+#             */
/*   Updated: 2025/04/12 14:44:47 by alisseye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <semaphore.h>

typedef struct s_sim
{
	struct timeval	start;
	sem_t			*state_sem;
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
	t_sim			*sim;
}	t_philo;

// Utils
int		ft_atoi(const char *str);
int		ft_isdigit(int c);
int		ft_isnumber(char *str);
int		timestamp(struct timeval *start);
void 	exit_sim(t_sim *sim, sem_t *forks, t_philo *philos);

#endif