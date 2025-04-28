/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisseye <alisseye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 12:58:31 by alisseye          #+#    #+#             */
/*   Updated: 2025/04/28 13:59:33 by alisseye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	get_last_meal(t_philo *philo)
{
	struct timeval	now;
	int				ms;

	sem_wait(philo->sim->meal_sem);
	gettimeofday(&now, NULL);
	ms = timestamp(&philo->sim->start_time) + \
		philo->sim->num_philo - timestamp(&philo->last_meal);
	sem_post(philo->sim->meal_sem);
	return (ms);
}

void	set_last_meal(t_philo *philo)
{
	sem_wait(philo->sim->meal_sem);
	gettimeofday(&philo->last_meal, NULL);
	sem_post(philo->sim->meal_sem);
}

void	increase_meals(t_philo *philo)
{
	sem_wait(philo->sim->meal_sem);
	philo->meals++;
	sem_post(philo->sim->meal_sem);
}

int	get_num_meals(t_philo *philo)
{
	int	meals;

	sem_wait(philo->sim->meal_sem);
	meals = philo->meals;
	sem_post(philo->sim->meal_sem);
	return (meals);
}
