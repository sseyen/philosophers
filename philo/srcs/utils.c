/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisseye <alisseye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 16:45:59 by alisseye          #+#    #+#             */
/*   Updated: 2025/04/14 17:16:36 by alisseye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	act(t_sim *sim, int ms)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	while (get_simstate(sim))
	{
		if (timestamp(&now) >= ms)
			return ;
		usleep(100);
	}
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

void	mprintf(t_sim *sim, char *str, int timestamp, int id)
{
	pthread_mutex_lock(&sim->print_mutex);
	printf(str, timestamp, id);
	pthread_mutex_unlock(&sim->print_mutex);
}
