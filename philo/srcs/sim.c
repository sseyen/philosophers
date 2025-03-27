/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisseye <alisseye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 15:20:42 by alisseye          #+#    #+#             */
/*   Updated: 2025/03/27 14:54:45 by alisseye         ###   ########.fr       */
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

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!get_simstate(philo->sim))
		;
	while (get_simstate(philo->sim) && philo->meals != philo->sim->num_meals)
	{
		eat(philo);
		philo->meals++;
		if (philo->meals == philo->sim->num_meals)
			break ;
		if (!get_simstate(philo->sim))
			break ;
		printf("%d %d is sleeping\n", timestamp(&philo->sim->start), philo->id);
		usleep(philo->sim->time_to_sleep * 1000);
		if (!get_simstate(philo->sim))
			break ;
		printf("%d %d is thinking\n", timestamp(&philo->sim->start), philo->id);
	}
	return (NULL);
}

void	check_sim(t_sim *sim, t_philo *philo)
{
	int	i;

	while (get_simstate(sim))
	{
		i = 0;
		while (i < sim->num_philo)
		{
			if (timestamp(&philo[i].last_meal) >= sim->time_to_die)
			{
				set_simstate(sim, 0);
				printf("%d %d died\n", \
					timestamp(&philo->sim->start), philo[i].id);
				return ;
			}
			i++;
		}
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
	check_sim(sim, philos);
	i = 0;
	while (i < sim->num_philo)
		pthread_join(philos[i++].thread, NULL);
}
