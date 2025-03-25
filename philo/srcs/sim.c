/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisseye <alisseye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 15:20:42 by alisseye          #+#    #+#             */
/*   Updated: 2025/03/26 00:08:52 by alisseye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	set_simstate(t_sim *sim, int state)
{
	pthread_mutex_lock(&sim->state_mutex);
	if (state == sim->state)
	{
		pthread_mutex_unlock(&sim->state_mutex);
		return (0);
	}
	sim->state = state;
	pthread_mutex_unlock(&sim->state_mutex);
	return (1);
}

int	get_simstate(t_sim *sim)
{
	int	state;

	pthread_mutex_lock(&sim->state_mutex);
	state = sim->state;
	pthread_mutex_unlock(&sim->state_mutex);
	return (state);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!get_simstate(philo->sim))
		;
	while (get_simstate(philo->sim) && philo->meals != philo->sim->num_meals)
	{
		if (!eat(philo))
			return (die(philo), NULL);
		philo->meals++;
		if (philo->meals == philo->sim->num_meals)
			break ;
		if (timestamp(&philo->last_meal) > philo->sim->time_to_die || \
			!get_simstate(philo->sim))
			return (die(philo), NULL);
		printf("%d %d is sleeping\n", timestamp(&philo->sim->start), philo->id);
		usleep(philo->sim->time_to_sleep * 1000);
		if (timestamp(&philo->last_meal) > philo->sim->time_to_die || \
			!get_simstate(philo->sim))
			return (die(philo), NULL);
		printf("%d %d is thinking\n", timestamp(&philo->sim->start), philo->id);
	}
	return (NULL);
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
	{
		philos[i].last_meal = sim->start;
		i++;
	}
	set_simstate(sim, 1);
	i = 0;
	while (i < sim->num_philo)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
}
