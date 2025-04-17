/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisseye <alisseye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 15:06:25 by alisseye          #+#    #+#             */
/*   Updated: 2025/04/17 15:16:21 by alisseye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	monitor()
{
	
}

void	run_sim(t_sim *sim, t_philo *philos, sem_t *forks)
{
	int	i;

	i = 0;
	while (i < sim->num_philo)
	{
		philos[i].pid = fork();
		if (philos[i].pid == 0)
		{
			philo_main(&philos[i], sim);
			exit(0);
		}
		i++;
	}
	sem_post(sim->state_sem);
	monitor(sim);
	i = 0;
	while (i < sim->num_philo)
	{
		waitpid(philos[i].pid, NULL, 0);
		i++;
	}
}
