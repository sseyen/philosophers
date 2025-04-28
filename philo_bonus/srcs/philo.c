/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisseye <alisseye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 19:03:57 by alisseye          #+#    #+#             */
/*   Updated: 2025/04/28 14:32:39 by alisseye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	*monitor_philo(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (get_num_meals(philo) == philo->sim->num_meals)
			break ;
		if (get_last_meal(philo) > philo->sim->time_to_die)
			exit(1);
		usleep(100);
	}
	return (NULL);
}

static void	eat(t_philo *philo)
{
	sem_wait(philo->sim->forks_sem);
	sem_wait(philo->sim->forks_sem);
	sprint(philo->sim, "has taken a fork", \
		timestamp(&philo->last_meal), philo->id);
	sprint(philo->sim, "is eating", \
		timestamp(&philo->last_meal), philo->id);
	act(philo->sim->time_to_eat);
	gettimeofday(&philo->last_meal, NULL);
	sem_post(philo->sim->forks_sem);
	sem_post(philo->sim->forks_sem);
}

static void	philo_routine(t_philo *philo, t_sim *sim)
{
	while (get_num_meals(philo) != sim->num_meals)
	{
		eat(philo);
		increase_meals(philo);
		if (philo->meals == sim->num_meals)
			break ;
		sprint(sim, "is sleeping", timestamp(&philo->last_meal), philo->id);
		act(philo->sim->time_to_sleep);
		sprint(sim, "is thinking", timestamp(&philo->last_meal), philo->id);
	}
}

int	philo_main(t_philo *philo, t_sim *sim)
{
	pthread_t	monitor;

	while (timestamp(&philo->sim->start_time) < philo->sim->num_philo)
	{
		gettimeofday(&philo->last_meal, NULL);
		usleep(100);
	}
	pthread_create(&monitor, NULL, &monitor_philo, philo);
	if (philo->id % 2 == 0)
		usleep(1000);
	philo_routine(philo, sim);
	pthread_join(monitor, NULL);
	exit(0);
}
