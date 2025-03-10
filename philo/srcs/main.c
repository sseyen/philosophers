/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisseye <alisseye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:37:10 by alisseye          #+#    #+#             */
/*   Updated: 2025/03/10 17:36:29 by alisseye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	parse_args(int argc, char **argv, t_sim *sim)
{
	if (argc < 5 || argc > 6)
	{
		printf("Error: wrong number of arguments\n");
		return (0);
	}
	if (!ft_isnumber(argv[1]) || !ft_isnumber(argv[2]) || !ft_isnumber(argv[3]) \
		|| !ft_isnumber(argv[4]) || (argc == 6 && !ft_isnumber(argv[5])))
	{
		printf("Error: arguments must be positive numbers\n");
		return (0);
	}
	sim->num_philo = ft_atoi(argv[1]);
	sim->time_to_die = ft_atoi(argv[2]);
	sim->time_to_eat = ft_atoi(argv[3]);
	sim->time_to_sleep = ft_atoi(argv[4]);
	sim->num_meals = -1;
	if (argc == 6)
		sim->num_meals = ft_atoi(argv[5]);
	if (sim->num_philo < 1 || sim->time_to_die < 0 || sim->time_to_eat < 0 \
		|| sim->time_to_sleep < 0 || sim->num_meals < -1)
	{
		printf("Error: arguments must be positive numbers\n");
		return (0);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	pthread_mutex_t	*forks;
	t_philo			*philos;
	t_sim			sim;

	if (!parse_args(argc, argv, &sim))
		return (1);
	forks = init_forks(&sim);
	if (!forks)
		return (1);
	philos = init_philos(&sim, forks);
	if (!philos)
	{
		exit_sim(&sim, forks, NULL);
		return (1);
	}
	sim.all_alive = 1;
	if (pthread_mutex_init(&sim.all_alive_mutex, NULL))
	{
		printf("Error: mutex init failed\n");
		exit_sim(&sim, forks, philos);
		return (1);
	}
	run_sim(&sim, philos, forks);
	pthread_mutex_destroy(&sim.all_alive_mutex);
	return (0);
}
