/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisseye <alisseye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 12:07:57 by alisseye          #+#    #+#             */
/*   Updated: 2025/04/14 12:51:42 by alisseye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void	put_fork(t_philo *philo)
{
	if (get_forkstate(philo->left_fork) == philo->id)
		set_forkstate(philo, philo->left_fork, 0);
	if (get_forkstate(philo->right_fork) == philo->id)
		set_forkstate(philo, philo->right_fork, 0);
}

void	pick_fork(t_philo *philo, t_fork *first, t_fork *second)
{
	if (!set_forkstate(philo, first, 1))
		return ;
	if (!get_simstate(philo->sim))
		return (put_fork(philo));
	if (!set_forkstate(philo, second, 1))
		return (put_fork(philo));
}

void	eat(t_philo *philo)
{
	pick_fork(philo, philo->left_fork, philo->right_fork);
	if (!get_simstate(philo->sim))
		return (put_fork(philo));
	mprintf(philo->sim, "%d %d has taken a fork\n", \
		timestamp(&philo->sim->start), philo->id);
	if (!get_simstate(philo->sim))
		return (put_fork(philo));
	mprintf(philo->sim, "%d %d is eating\n", \
		timestamp(&philo->sim->start), philo->id);
	usleep(philo->sim->time_to_eat * 1000);
	set_last_meal(philo);
	put_fork(philo);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!get_simstate(philo->sim))
		;
	if (philo->id % 2 != 0)
		usleep(2000);
	while (get_simstate(philo->sim) && philo->meals != philo->sim->num_meals)
	{
		eat(philo);
		increase_meals(philo);
		if (get_meals(philo) == philo->sim->num_meals)
			break ;
		if (!get_simstate(philo->sim))
			break ;
		mprintf(philo->sim, "%d %d is sleeping\n", \
			timestamp(&philo->sim->start), philo->id);
		usleep(philo->sim->time_to_sleep * 1000);
		if (!get_simstate(philo->sim))
			break ;
		mprintf(philo->sim, "%d %d is thinking\n", \
			timestamp(&philo->sim->start), philo->id);
	}
	return (NULL);
}
