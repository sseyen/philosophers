/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisseye <alisseye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 18:43:47 by alisseye          #+#    #+#             */
/*   Updated: 2025/04/14 17:16:46 by alisseye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_last_meal(t_philo *philo)
{
	struct timeval	now;
	int				time;

	gettimeofday(&now, NULL);
	time = (now.tv_sec - philo->last_meal.tv_sec) * 1000 + \
		(now.tv_usec - philo->last_meal.tv_usec) / 1000;
	return (time);
}

int	set_last_meal(t_philo *philo)
{
	gettimeofday(&philo->last_meal, NULL);
	return (1);
}

int	get_meals(t_philo *philo)
{
	int	meals;

	pthread_mutex_lock(&philo->meal_mutex);
	meals = philo->meals;
	pthread_mutex_unlock(&philo->meal_mutex);
	return (meals);
}

void	increase_meals(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_mutex);
	philo->meals++;
	pthread_mutex_unlock(&philo->meal_mutex);
}
