/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisseye <alisseye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:37:10 by alisseye          #+#    #+#             */
/*   Updated: 2025/08/31 21:27:14 by alisseye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_philo			*philos;
	pthread_mutex_t	*forks;
	t_sim			sim;

	if (!parse_args(argc, argv, &sim))
		return (1);
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
