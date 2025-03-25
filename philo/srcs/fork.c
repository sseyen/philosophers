/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisseye <alisseye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 22:12:12 by alisseye          #+#    #+#             */
/*   Updated: 2025/03/25 23:42:35 by alisseye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_forkstate(t_fork *fork)
{
	int	state;

	pthread_mutex_lock(&fork->state_mutex);
	state = fork->state;
	pthread_mutex_unlock(&fork->state_mutex);
	return (state);
}

int	set_forkstate(t_philo *philo, t_fork *fork, int state)
{
	while (state && get_forkstate(fork))
		if (timestamp(&philo->last_meal) > philo->sim->time_to_die || \
			!get_simstate(philo->sim))
			return (0);
	pthread_mutex_lock(&fork->state_mutex);
	if (state)
		fork->state = philo->id;
	else
		fork->state = 0;
	pthread_mutex_unlock(&fork->state_mutex);
	return (1);
}
