/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisseye <alisseye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 19:03:57 by alisseye          #+#    #+#             */
/*   Updated: 2025/04/12 14:49:00 by alisseye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	philo_main(t_philo *philo, t_sim *sim)
{
	pthread_t	monitor_thread;

	while (!sem)
		usleep(100);
	philo->meals = 0;
	gettimeofday(&sim->start, NULL);
	philo->last_meal = philo->sim->start;
	
	return (0);
}