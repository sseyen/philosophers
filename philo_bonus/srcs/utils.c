/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisseye <alisseye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 16:45:59 by alisseye          #+#    #+#             */
/*   Updated: 2025/04/28 13:06:29 by alisseye         ###   ########.fr       */
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

void	act(int ms)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	while (timestamp(&now) < ms)
		usleep(100);
}

void	sprint(t_sim *sim, char *str, int timestamp, int id)
{
	sem_wait(sim->print_sem);
	printf("%d %d %s\n", timestamp, id, str);
	sem_post(sim->print_sem);
}

void	exit_sim(t_sim *sim, sem_t *forks, t_philo *philos)
{
	if (sim)
	{
		sem_close(sim->print_sem);
		sem_unlink("/print");
	}
	if (forks)
	{
		sem_close(forks);
		sem_unlink("/forks");
	}
	if (philos)
		free(philos);
}
