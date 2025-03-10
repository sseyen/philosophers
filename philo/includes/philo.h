/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisseye <alisseye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:37:03 by alisseye          #+#    #+#             */
/*   Updated: 2025/03/10 15:11:02 by alisseye         ###   ########.fr       */
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
	int	num_philo;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	num_meals;
	int	all_alive;
}	t_sim;

typedef struct s_philo
{
	int				id;
	int				alive;
	int				meals;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	struct timeval	last_meal;
	t_sim			*sim;
}	t_philo;

// Utils calculations
int				ft_atoi(const char *str);
int				ft_isdigit(int c);
int				ft_isnumber(char *str);
int				get_timestamp(struct timeval *start);
pthread_mutex_t	*init_forks(t_sim *sim);

#endif