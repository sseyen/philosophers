/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisseye <alisseye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 18:43:47 by alisseye          #+#    #+#             */
/*   Updated: 2025/04/12 18:43:53 by alisseye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_meals(t_philo *philo)
{
	int	meals;

	pthread_mutex_lock(&philo->meal_mutex);
	meals = philo->meals;
	pthread_mutex_unlock(&philo->meal_mutex);
	return (meals);
}

void increase_meals(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_mutex);
	philo->meals++;
	pthread_mutex_unlock(&philo->meal_mutex);
}
