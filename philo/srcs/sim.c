/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisseye <alisseye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 15:20:42 by alisseye          #+#    #+#             */
/*   Updated: 2025/09/13 13:29:25 by alisseye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	kill_philo(t_sim *sim, t_philo *philo)
{
	usleep(100);
	pthread_mutex_lock(&sim->print_mutex);
	set_simstate(sim, 0);
	printf("%d %d %s\n", \
		timestamp(&sim->start) - (int)(philo->sim->num_philo * 0.2), \
		philo->id, DEAD);
	pthread_mutex_unlock(&sim->print_mutex);
}

void	monitor(t_sim *sim, t_philo *philo)
{
	int	i;
	int	philos_ate;

	while (timestamp(&sim->start) < (int)(philo->sim->num_philo * 0.2) + 5)
		usleep(100);
	while (1)
	{
		i = 0;
		philos_ate = 0;
		while (i < sim->num_philo)
		{
			if (get_meals(&philo[i]) != sim->num_meals && \
				get_last_meal(&philo[i]) >= sim->time_to_die)
			{
				kill_philo(sim, &philo[i]);
				return ;
			}
			if (get_meals(&philo[i]) == sim->num_meals)
				philos_ate++;
			i++;
		}
		if (philos_ate == sim->num_philo)
			return (set_simstate(sim, 0));
	}
}

void	exit_sim(t_sim *sim, pthread_mutex_t *forks, t_philo *philos)
{
	int	i;

	i = 0;
	if (forks)
	{
		while (i < sim->num_philo)
		{
			pthread_mutex_destroy(&forks[i]);
			i++;
		}
		free(forks);
	}
	if (philos)
	{
		free(philos);
	}
	if (sim)
	{
		pthread_mutex_destroy(&sim->state_mutex);
		pthread_mutex_destroy(&sim->print_mutex);
	}
}

void	run_sim(t_sim *sim, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < sim->num_philo)
	{
		pthread_create(&philos[i].thread, NULL, &philo_routine, &philos[i]);
		i++;
	}
	i = 0;
	gettimeofday(&sim->start, NULL);
	set_simstate(sim, 1);
	monitor(sim, philos);
	i = 0;
	while (i < sim->num_philo)
		pthread_join(philos[i++].thread, NULL);
}
