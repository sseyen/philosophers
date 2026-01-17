/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisseye <alisseye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 12:07:57 by alisseye          #+#    #+#             */
/*   Updated: 2026/01/17 18:49:47 by alisseye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	act(t_sim *sim, int ms)
{
	long long	target_us;
	long long	now;

	target_us = elapsed_us(&sim->start) + (ms * 1000);
	now = elapsed_us(&sim->start);
	while (get_simstate(sim) && now < target_us)
	{
		usleep(500);
		now = elapsed_us(&sim->start);
	}
}

void	eat(t_philo *philo)
{
	if (philo->id % 2 != 0)
	{
		pthread_mutex_lock(philo->left_fork);
		print_status(philo->sim, &philo->sim->start, philo->id, FORK_TAKEN);
		pthread_mutex_lock(philo->right_fork);
		print_status(philo->sim, &philo->sim->start, philo->id, FORK_TAKEN);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		print_status(philo->sim, &philo->sim->start, philo->id, FORK_TAKEN);
		pthread_mutex_lock(philo->left_fork);
		print_status(philo->sim, &philo->sim->start, philo->id, FORK_TAKEN);
	}
	print_status(philo->sim, &philo->sim->start, philo->id, EATING);
	set_last_meal(philo);
	act(philo->sim, philo->sim->time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (timestamp(&philo->sim->start) < philo->sim->delay)
		usleep(100);
	set_last_meal(philo);
	if (philo->id % 2 == 0)
		act(philo->sim, philo->sim->time_to_eat / 2);
	while (get_meals(philo) != philo->sim->num_meals)
	{
		eat(philo);
		increase_meals(philo);
		if (get_meals(philo) == philo->sim->num_meals)
			break ;
		print_status(philo->sim, &philo->sim->start, philo->id, SLEEPING);
		act(philo->sim, philo->sim->time_to_sleep);
		print_status(philo->sim, &philo->sim->start, philo->id, THINKING);
		if (!get_simstate(philo->sim))
			break ;
	}
	return (NULL);
}
