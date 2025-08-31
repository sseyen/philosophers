/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisseye <alisseye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 15:20:42 by alisseye          #+#    #+#             */
/*   Updated: 2025/08/31 21:43:39 by alisseye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_simstate(t_sim *sim, int state)
{
	pthread_mutex_lock(&sim->state_mutex);
	sim->state = state;
	pthread_mutex_unlock(&sim->state_mutex);
}

int	get_simstate(t_sim *sim)
{
	int	state;

	usleep(1);
	pthread_mutex_lock(&sim->state_mutex);
	state = sim->state;
	pthread_mutex_unlock(&sim->state_mutex);
	return (state);
}

void	monitor(t_sim *sim, t_philo *philo)
{
	int	i;
	int	philos_ate;

	while (1)
	{
		i = 0;
		philos_ate = 0;
		while (i < sim->num_philo)
		{
			if (get_meals(&philo[i]) != sim->num_meals && \
				get_last_meal(&philo[i]) >= sim->time_to_die)
			{
				pthread_mutex_lock(&sim->print_mutex);
				set_simstate(sim, 0);
				printf("%d %d %s\n", timestamp(&sim->start), philo[i].id, DEAD);
				pthread_mutex_unlock(&sim->print_mutex);
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
	usleep(1000);
	monitor(sim, philos);
	i = 0;
	while (i < sim->num_philo)
		pthread_join(philos[i++].thread, NULL);
}
