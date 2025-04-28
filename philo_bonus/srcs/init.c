/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisseye <alisseye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 14:38:04 by alisseye          #+#    #+#             */
/*   Updated: 2025/04/28 13:22:11 by alisseye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	init_sems(t_sim *sim, sem_t **forks)
{
	sim->print_sem = sem_open("/print", O_CREAT, 0644, 1);
	if (sim->print_sem == SEM_FAILED)
	{
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
		(*philos)[i].pid = -1;
		(*philos)[i].last_meal = sim->start_time;
		(*philos)[i].id = i + 1;
		(*philos)[i].meals = 0;
		(*philos)[i].sim = sim;
		(*philos)[i].meal_sem = sem_open("/meal", O_CREAT, 0644, 1);
		i++;
	}
	return (1);
}
