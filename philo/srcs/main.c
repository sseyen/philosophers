/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisseye <alisseye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:37:10 by alisseye          #+#    #+#             */
/*   Updated: 2025/09/14 22:28:12 by alisseye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	one_philo(t_sim *sim)
{
	printf("0 1 %s\n", FORK_TAKEN);
	usleep(sim->time_to_die * 1000);
	printf("%d 1 %s\n", sim->time_to_die, DEAD);
}

int	main(int argc, char **argv)
{
	t_philo			*philos;
	pthread_mutex_t	*forks;
	t_sim			sim;

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
	if (pthread_mutex_init(&sim.state_mutex, NULL))
		return (printf("Error: state mutex init failed\n"),
			exit_sim(NULL, forks, philos), 1);
	if (pthread_mutex_init(&sim.print_mutex, NULL))
		return (printf("Error: print mutex init failed\n"),
			pthread_mutex_destroy(&sim.state_mutex),
			exit_sim(NULL, forks, philos), 1);
	sim.state = 0;
	run_sim(&sim, philos);
	exit_sim(&sim, forks, philos);
	return (0);
}
