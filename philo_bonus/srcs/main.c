/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisseye <alisseye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 14:19:07 by alisseye          #+#    #+#             */
/*   Updated: 2025/04/17 15:11:33 by alisseye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int argc, char **argv)
{
	t_philo	*philos;
	sem_t	*forks;
	t_sim	sim;

	if (!parse_args(argc, argv, &sim))
		return (1);
	if (!init_sems(&sim, &forks))
		return (1);
	if (!init_philos(&sim, &philos))
	{
		exit_sim(&sim, forks, NULL);
		return (1);
	}
	run_sim(&sim, philos, forks);
	exit_sim(&sim, forks, philos);
	return (0);
}
