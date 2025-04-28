/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisseye <alisseye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 15:06:25 by alisseye          #+#    #+#             */
/*   Updated: 2025/04/28 15:25:54 by alisseye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	update_philo(t_philo *philos, pid_t pid)
{
	int	i;

	i = 0;
	while (i < philos->sim->num_philo)
	{
		if (philos[i].pid == pid)
		{
			philos[i].pid = -1;
			break ;
		}
		i++;
	}
}

static void	kill_all(t_sim *sim, t_philo *philos, pid_t pid)
{
	int	i;
	int	id;

	i = 0;
	while (i < sim->num_philo)
	{
		if (philos[i].pid != -1 && philos[i].pid != pid)
			kill(philos[i].pid, SIGKILL);
		if (philos[i].pid == pid)
			id = i + 1;
		i++;
	}
	printf("%d %d died\n", \
		timestamp(&sim->start_time) - sim->num_philo, id);
}

static void	fork_philos(t_philo *philos, t_sim *sim)
{
	int	i;

	i = 0;
	while (i < sim->num_philo)
	{
		philos[i].last_meal = sim->start_time;
		philos[i].pid = fork();
		if (philos[i].pid == 0)
			philo_main(&philos[i], sim, philos);
		if (philos[i].pid < 0)
		{
			printf("Error: Fork failed\n");
			kill_all(sim, philos, -1);
			exit(1);
		}
		i++;
	}
}

void	run_sim(t_sim *sim, t_philo *philos)
{
	int		i;
	pid_t	pid;
	int		status;

	gettimeofday(&sim->start_time, NULL);
	fork_philos(philos, sim);
	i = 0;
	while (i < sim->num_philo)
	{
		pid = waitpid(-1, &status, 0);
		if (status >> 8 == 0)
			update_philo(philos, pid);
		if (status >> 8 == 1)
		{
			kill_all(sim, philos, pid);
			break ;
		}
		i++;
	}
}
