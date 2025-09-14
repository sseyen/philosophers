/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisseye <alisseye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 16:45:59 by alisseye          #+#    #+#             */
/*   Updated: 2025/09/13 13:29:41 by alisseye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_simstate(t_sim *sim, int state)
{
	pthread_mutex_lock(&sim->state_mutex);
	sim->state = state;
	pthread_mutex_unlock(&sim->state_mutex);
}

int	get_simstate(t_sim *sim)
{
	int	state;

	pthread_mutex_lock(&sim->state_mutex);
	state = sim->state;
	pthread_mutex_unlock(&sim->state_mutex);
	return (state);
}

void	act(int ms)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	while (timestamp(&now) < ms)
		usleep(100);
}

int	timestamp(struct timeval *start)
{
	struct timeval	now;
	int				ms;

	gettimeofday(&now, NULL);
	ms = ((now.tv_sec - start->tv_sec) * 1000) + \
		((now.tv_usec - start->tv_usec) / 1000);
	return (ms);
}

void	print_status(t_sim *sim, struct timeval *time, int id, char *status)
{
	pthread_mutex_lock(&sim->print_mutex);
	if (get_simstate(sim) == 0)
	{
		pthread_mutex_unlock(&sim->print_mutex);
		return ;
	}
	printf("%d %d %s\n", \
		timestamp(time) - (int)(sim->num_philo * 0.2), id, status);
	pthread_mutex_unlock(&sim->print_mutex);
}
