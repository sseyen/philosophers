/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisseye <alisseye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 17:07:52 by alisseye          #+#    #+#             */
/*   Updated: 2025/03/25 22:45:57 by alisseye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_state_mutexes(t_fork *forks, t_sim *sim)
{
	int	i;

	i = 0;
	while (i < sim->num_philo)
	{
		if (pthread_mutex_init(&forks[i].state_mutex, NULL) != 0)
		{
			while (i > 0)
				pthread_mutex_destroy(&forks[--i].state_mutex);
			while (i < sim->num_philo)
				pthread_mutex_destroy(&forks[i++].mutex);
			free(forks);
			return (0);
		}
		forks[i].state = 0;
		i++;
	}
	return (1);
}

int	init_mutexes(t_fork *forks, t_sim *sim)
{
	int	i;

	i = 0;
	while (i < sim->num_philo)
	{
		if (pthread_mutex_init(&forks[i].mutex, NULL) != 0)
		{
			while (i > 0)
				pthread_mutex_destroy(&forks[--i].mutex);
			free(forks);
			return (0);
		}
		i++;
	}
	return (1);
}

t_fork	*init_forks(t_sim *sim)
{
	t_fork			*forks;

	forks = malloc(sizeof(t_fork) * sim->num_philo);
	if (!forks)
	{
		printf("Error: malloc failed (forks)\n");
		return (NULL);
	}
	if (!init_mutexes(forks, sim))
	{
		printf("Error: failed to init mutexes\n");
		return (NULL);
	}
	if (!init_state_mutexes(forks, sim))
	{
		printf("Error: failed to init state mutexes\n");
		return (NULL);
	}
	return (forks);
}

t_philo	*init_philos(t_sim *sim, t_fork *forks)
{
	t_philo	*philos;
	int		i;

	philos = malloc(sizeof(t_philo) * sim->num_philo);
	if (!philos)
	{
		printf("Error: malloc failed (philos)\n");
		return (NULL);
	}
	i = 0;
	while (i < sim->num_philo)
	{
		philos[i].id = i + 1;
		philos[i].meals = 0;
		philos[i].left_fork = &forks[i];
		if (philos[i].id == 1)
			philos[i].right_fork = &forks[sim->num_philo - 1];
		else
			philos[i].right_fork = &forks[i - 1];
		philos[i].sim = sim;
		i++;
	}
	return (philos);
}
