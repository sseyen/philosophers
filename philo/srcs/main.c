/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisseye <alisseye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:37:10 by alisseye          #+#    #+#             */
/*   Updated: 2025/03/10 15:17:39 by alisseye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (philo->sim->all_alive)
	{
		// Think
		// Take forks
		// Eat
		// Put forks
		// Sleep
	}
	return (NULL);
}

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
	struct timeval	start;
	t_sim			sim;

	if (!parse_args(argc, argv, &sim))
		return (1);
	sim.all_alive = 1;
	forks = init_forks(&sim);
	if (!forks)
		return (1);
	gettimeofday(&start, NULL);
	free(forks);
	return (0);
}
