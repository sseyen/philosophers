/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisseye <alisseye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 16:45:59 by alisseye          #+#    #+#             */
/*   Updated: 2025/04/16 19:59:44 by alisseye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	timestamp(struct timeval *start)
{
	struct timeval	now;
	int				ms;

	gettimeofday(&now, NULL);
	ms = ((now.tv_sec - start->tv_sec) * 1000) + \
		((now.tv_usec - start->tv_usec) / 1000);
	return (ms);
}

void	act(t_sim *sim, int ms)
{
	struct timeval	now;
	int i = 0;

	(void)sim;
	gettimeofday(&now, NULL);
	while (i++ < 100)
	{
		if (timestamp(&now) >= ms)
			return ;
		usleep(100);
	}
}

void	exit_sim(t_sim *sim, sem_t *forks, t_philo *philos)
{
	if (sim->state_sem)
	{
		sem_close(sim->print_sem);
		sem_unlink("/print");
		sem_close(sim->state_sem);
		sem_unlink("/state");
	}
	if (forks)
	{
		sem_close(forks);
		sem_unlink("/forks");
	}
	if (philos)
		free(philos);
}
