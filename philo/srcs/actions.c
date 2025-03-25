/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisseye <alisseye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 12:07:57 by alisseye          #+#    #+#             */
/*   Updated: 2025/03/26 00:06:31 by alisseye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	die(t_philo *philo)
{
	if (!get_simstate(philo->sim))
		return ;
	if (!set_simstate(philo->sim, 0))
		return ;
	printf("%d %d died\n", timestamp(&philo->sim->start), philo->id);
}

void	put_fork(t_philo *philo)
{
	if (get_forkstate(philo->left_fork) == philo->id)
	{
		pthread_mutex_unlock(&philo->left_fork->mutex);
		set_forkstate(philo, philo->left_fork, 0);
	}
	if (get_forkstate(philo->right_fork) == philo->id)
	{
		pthread_mutex_unlock(&philo->right_fork->mutex);
		set_forkstate(philo, philo->right_fork, 0);
	}
}

int	pick_fork(t_philo *philo, t_fork *first, t_fork *second)
{
	if (!set_forkstate(philo, first, 1))
		return (0);
	pthread_mutex_lock(&first->mutex);
	if (!get_simstate(philo->sim) || \
		timestamp(&philo->last_meal) > philo->sim->time_to_die)
		return (put_fork(philo), 0);
	if (!set_forkstate(philo, second, 1))
		return (put_fork(philo), 1);
	pthread_mutex_lock(&second->mutex);
	return (1);
}

int	eat(t_philo *philo)
{
	if (philo->id % 2)
	{
		if (!pick_fork(philo, philo->left_fork, philo->right_fork))
			return (0);
	}
	else
	{
		if (!pick_fork(philo, philo->right_fork, philo->left_fork))
			return (0);
	}
	if (timestamp(&philo->last_meal) > philo->sim->time_to_die \
		|| !get_simstate(philo->sim))
		return (put_fork(philo), 0);
	printf("%d %d has taken a fork\n", \
		timestamp(&philo->sim->start), philo->id);
	if (timestamp(&philo->last_meal) > philo->sim->time_to_die \
		|| !get_simstate(philo->sim))
		return (put_fork(philo), 0);
	printf("%d %d is eating\n", timestamp(&philo->sim->start), philo->id);
	usleep(philo->sim->time_to_eat * 1000);
	gettimeofday(&philo->last_meal, NULL);
	put_fork(philo);
	return (1);
}
