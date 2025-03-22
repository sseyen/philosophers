/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisseye <alisseye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 15:20:42 by alisseye          #+#    #+#             */
/*   Updated: 2025/03/13 12:43:42 by alisseye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	die(t_philo *philo)
{
	pthread_mutex_lock(&philo->sim->all_alive_mutex);
	if (philo->sim->all_alive)
	{
		printf("%d %d died\n", timestamp(&philo->sim->start), philo->id);
		philo->sim->all_alive = 0;
	}
	usleep(1000);
	pthread_mutex_unlock(&philo->sim->all_alive_mutex);
}

int	eat(t_philo *philo)
{
	if (philo->id % 2)
	{
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(philo->right_fork);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		pthread_mutex_lock(philo->left_fork);
	}
	if (timestamp(&philo->last_meal) > philo->sim->time_to_die \
		|| !philo->sim->all_alive)
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return (0);
	}
	printf("%d %d has taken a fork\n", \
		timestamp(&philo->sim->start), philo->id);
	printf("%d %d is eating\n", timestamp(&philo->sim->start), philo->id);
	usleep(philo->sim->time_to_eat * 1000);
	return (1);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (philo->sim->all_alive && philo->meals != philo->sim->num_meals)
	{
		eat(philo);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		gettimeofday(&philo->last_meal, NULL);
		if (philo->sim->num_meals > 0)
			philo->meals++;
		printf("%d %d is sleeping\n", timestamp(&philo->sim->start), philo->id);
		usleep(philo->sim->time_to_sleep * 1000);
		printf("%d %d is thinking\n", timestamp(&philo->sim->start), philo->id);
	}
	return (NULL);
}

int	all_ate(t_sim *sim, t_philo *philos)
{
	int	i;

	i = 0;
	while (sim->num_meals > 0 && i < sim->num_philo)
	{
		if (philos[i].meals != sim->num_meals)
			return (0);
		i++;
	}
	return (1);
}

void	run_sim(t_sim *sim, t_philo *philos, pthread_mutex_t *forks)
{
	int				i;

	gettimeofday(&sim->start, NULL);
	i = 0;
	while (i < sim->num_philo)
	{
		philos[i].last_meal = sim->start;
		pthread_create(&philos[i].thread, NULL, &philo_routine, &philos[i]);
		i++;
	}
	i = 0;
	while (i < sim->num_philo)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
	exit_sim(sim, forks, philos);
}
