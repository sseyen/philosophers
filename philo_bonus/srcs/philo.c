/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisseye <alisseye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 19:03:57 by alisseye          #+#    #+#             */
/*   Updated: 2025/04/16 19:54:57 by alisseye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	philo_main(t_philo *philo, t_sim *sim)
{
	while (!get_simstate(sim))
		usleep(100);
	if (philo->id % 2 == 0)
		usleep(1000);
	while (get_simstate(sim) && philo->meals != sim->num_meals)
	{
		eat(philo);
		increase_meals(philo);
		if (get_simstate(sim))
			sleep_philo(philo);
		if (get_simstate(sim))
			think(philo);
	}
	return (0);
}