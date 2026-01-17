/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisseye <alisseye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 17:07:52 by alisseye          #+#    #+#             */
/*   Updated: 2026/01/17 18:23:45 by alisseye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	setup_philo(t_philo *philo, pthread_mutex_t *forks, t_sim *sim,
			int idx)
{
	philo->id = idx + 1;
	philo->meals = 0;
	philo->left_fork = &forks[idx];
	if (philo->id == 1)
		philo->right_fork = &forks[sim->num_philo - 1];
	else
		philo->right_fork = &forks[idx - 1];
	philo->sim = sim;
}

int	init_state_mutexes(pthread_mutex_t *forks, t_sim *sim)
{
	int	i;

	i = 0;
	while (i < sim->num_philo)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
		{
			while (i > 0)
				pthread_mutex_destroy(&forks[--i]);
			free(forks);
			return (0);
		}
		i++;
	}
	return (1);
}

pthread_mutex_t	*init_forks(t_sim *sim)
{
	pthread_mutex_t	*forks;

	forks = malloc(sizeof(pthread_mutex_t) * sim->num_philo);
	if (!forks)
	{
		printf("Error: malloc failed (forks)\n");
		return (NULL);
	}
	if (!init_state_mutexes(forks, sim))
	{
		printf("Error: failed to init state mutexes\n");
		return (NULL);
	}
	return (forks);
}

int	init_meal_mutexes(t_philo *philos, t_sim *sim)
{
	int	i;

	i = 0;
	while (i < sim->num_philo)
	{
		if (pthread_mutex_init(&philos[i].meal_mutex, NULL) != 0)
		{
			while (i > 0)
				pthread_mutex_destroy(&philos[--i].meal_mutex);
			free(philos);
			return (0);
		}
		i++;
	}
	return (1);
}

t_philo	*init_philos(t_sim *sim, pthread_mutex_t *forks)
{
	t_philo	*philos;
	int		i;

	philos = malloc(sizeof(t_philo) * sim->num_philo);
	if (!philos)
		return (printf("Error: malloc failed (philos)\n"), NULL);
	i = 0;
	while (i < sim->num_philo)
	{
		setup_philo(&philos[i], forks, sim, i);
		i++;
	}
	if (!init_meal_mutexes(philos, sim))
		return (printf("Error: failed to init meal mutexes\n"), NULL);
	i = 0;
	while (i < sim->num_philo)
		set_last_meal(&philos[i++]);
	return (philos);
}
