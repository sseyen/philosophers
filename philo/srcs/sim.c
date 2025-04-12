/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisseye <alisseye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 15:20:42 by alisseye          #+#    #+#             */
/*   Updated: 2025/03/27 15:12:40 by alisseye         ###   ########.fr       */
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

	usleep(100);
	pthread_mutex_lock(&sim->state_mutex);
	state = sim->state;
	pthread_mutex_unlock(&sim->state_mutex);
	return (state);
}

void	monitor(t_sim *sim, t_philo *philo)
{
	int	i;
	int	philos_ate;

	while (get_simstate(sim))
	{
		i = 0;
		philos_ate = 0;
		while (i < sim->num_philo)
		{
			if (get_meals(philo[i]) != sim->num_meals && \
				timestamp(&philo[i].last_meal) >= sim->time_to_die)
			{
				set_simstate(sim, 0);
				mprint(sim, "%d %d died\n", \
					timestamp(&philo->sim->start), philo[i].id);
				return ;
			}
			if (philo[i].meals == sim->num_meals)
				philos_ate++;
			i++;
		}
		if (philos_ate == sim->num_philo)
			return (set_simstate(sim, 0));
	}
}

void	exit_sim(t_sim *sim, t_fork *forks, t_philo *philos)
{
	int	i;

	i = 0;
	if (forks)
	{
		while (i < sim->num_philo)
		{
			pthread_mutex_destroy(&forks[i].state_mutex);
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
	while (i < sim->num_philo)
		philos[i++].last_meal = sim->start;
	set_simstate(sim, 1);
	monitor(sim, philos);
	i = 0;
	while (i < sim->num_philo)
		pthread_join(philos[i++].thread, NULL);
}
