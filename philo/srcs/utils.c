/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisseye <alisseye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 16:45:59 by alisseye          #+#    #+#             */
/*   Updated: 2026/01/17 18:54:20 by alisseye         ###   ########.fr       */
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

long long	elapsed_us(struct timeval *start)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return (((now.tv_sec - start->tv_sec) * 1000000)
		+ (now.tv_usec - start->tv_usec));
}

int	timestamp(struct timeval *start)
{
	return (elapsed_us(start) / 1000);
}

void	print_status(t_sim *sim, struct timeval *time, int id, \
					char *status)
{
	int	now_ms;

	pthread_mutex_lock(&sim->print_mutex);
	if (get_simstate(sim) == 0)
	{
		pthread_mutex_unlock(&sim->print_mutex);
		return ;
	}
	now_ms = timestamp(time) - sim->delay;
	printf("%d %d %s\n", now_ms, id, status);
	pthread_mutex_unlock(&sim->print_mutex);
}
