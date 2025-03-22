/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisseye <alisseye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 17:07:52 by alisseye          #+#    #+#             */
/*   Updated: 2025/03/22 20:03:17 by alisseye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

pthread_mutex_t	*init_forks(t_sim *sim)
{
	int				i;
	pthread_mutex_t	*forks;

	forks = malloc(sizeof(pthread_mutex_t) * sim->num_philo);
	if (!forks)
		return (printf("Error: malloc failed (forks)\n"), NULL);
	i = 0;
	while (i < sim->num_philo)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
		{
			while (i >= 0)
				pthread_mutex_destroy(&forks[i--]);
			free(forks);
			forks = NULL;
			return (printf("Error: failed to init forks\n"), NULL);
		}
		i++;
	}
	return (forks);
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
