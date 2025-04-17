/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisseye <alisseye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 14:38:04 by alisseye          #+#    #+#             */
/*   Updated: 2025/04/17 15:10:17 by alisseye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	init_sems(t_sim *sim, sem_t **forks)
{
	sim->state_sem = sem_open("/state", O_CREAT, 0644, 1);
	if (sim->state_sem == SEM_FAILED)
	{
		printf("Error: sim state sem init failed\n");
		return (0);
	}
	sem_wait(sim->state_sem);
	sim->print_sem = sem_open("/print", O_CREAT, 0644, 1);
	if (sim->print_sem == SEM_FAILED)
	{
		sem_close(sim->state_sem);
		sem_unlink("/state");
		printf("Error: print sem init failed\n");
		return (0);
	}
	*forks = sem_open("/forks", O_CREAT, 0644, sim->num_philo);
	if (*forks == SEM_FAILED)
	{
		exit_sim(sim, NULL, NULL);
		printf("Error: forks sem init failed\n");
		return (0);
	}
	return (1);
}

int	init_philos(t_sim *sim, t_philo **philos)
{
	int	i;

	*philos = malloc(sizeof(t_philo) * sim->num_philo);
	if (!(*philos))
	{
		printf("Error: malloc failed\n");
		return (0);
	}
	i = 0;
	while (i < sim->num_philo)
	{
		(*philos)[i].id = i + 1;
		(*philos)[i].meals = 0;
		(*philos)[i].sim = sim;
		i++;
	}
	return (1);
}
