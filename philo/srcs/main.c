/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisseye <alisseye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:37:10 by alisseye          #+#    #+#             */
/*   Updated: 2026/01/17 18:34:26 by alisseye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	one_philo(t_sim *sim)
{
	printf("0 1 %s\n", FORK_TAKEN);
	usleep(sim->time_to_die * 1000);
	printf("%d 1 %s\n", sim->time_to_die, DEAD);
}

static int	init_sim_mutexes(t_sim *sim)
{
	if (pthread_mutex_init(&sim->state_mutex, NULL))
		return (printf("Error: state mutex init failed\n"), 0);
	sim->state_mutex_ready = 1;
	if (pthread_mutex_init(&sim->print_mutex, NULL))
	{
		pthread_mutex_destroy(&sim->state_mutex);
		sim->state_mutex_ready = 0;
		return (printf("Error: print mutex init failed\n"), 0);
	}
	sim->print_mutex_ready = 1;
	return (1);
}

int	main(int argc, char **argv)
{
	t_philo			*philos;
	pthread_mutex_t	*forks;
	t_sim			sim;

	memset(&sim, 0, sizeof(sim));
	if (!parse_args(argc, argv, &sim))
		return (1);
	if (sim.num_philo == 1)
		return (one_philo(&sim), 0);
	forks = init_forks(&sim);
	if (!forks)
		return (1);
	philos = init_philos(&sim, forks);
	if (!philos)
		return (exit_sim(&sim, forks, NULL), 1);
	if (!init_sim_mutexes(&sim))
		return (exit_sim(&sim, forks, philos), 1);
	sim.state = 0;
	run_sim(&sim, philos);
	exit_sim(&sim, forks, philos);
	return (0);
}
