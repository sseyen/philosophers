/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisseye <alisseye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 12:07:57 by alisseye          #+#    #+#             */
/*   Updated: 2025/08/31 21:43:43 by alisseye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_philo *philo)
{
	if (philo->id % 2 != 0)
		pthread_mutex_lock(philo->left_fork);
	else
		pthread_mutex_lock(philo->right_fork);
	print_status(philo->sim, &philo->sim->start, philo->id, FORK_TAKEN);
	if (philo->id % 2 != 0)
		pthread_mutex_lock(philo->right_fork);
	else
		pthread_mutex_lock(philo->left_fork);
	print_status(philo->sim, &philo->sim->start, philo->id, FORK_TAKEN);
	print_status(philo->sim, &philo->sim->start, philo->id, EATING);
	act(philo->sim->time_to_eat);
	set_last_meal(philo);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!get_simstate(philo->sim))
		;
	set_last_meal(philo);
	if (philo->id % 2 != 0)
		usleep(1000);
	while (philo->meals != philo->sim->num_meals)
	{
		eat(philo);
		increase_meals(philo);
		if (get_meals(philo) == philo->sim->num_meals)
			break ;
		print_status(philo->sim, &philo->sim->start, philo->id, SLEEPING);
		act(philo->sim->time_to_sleep);
		print_status(philo->sim, &philo->sim->start, philo->id, THINKING);
		if (!get_simstate(philo->sim))
			break ;
	}
	return (NULL);
}
