/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisseye <alisseye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 14:19:07 by alisseye          #+#    #+#             */
/*   Updated: 2025/04/28 14:48:44 by alisseye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int argc, char **argv)
{
	t_philo	*philos;
	sem_t	*forks;
	t_sim	sim;

	sem_unlink("/print");
	sem_unlink("/meal");
	sem_unlink("/forks");
	if (!parse_args(argc, argv, &sim))
		return (1);
	if (!init_sems(&sim, &forks))
		return (1);
	sim.forks_sem = forks;
	if (!init_philos(&sim, &philos))
	{
		exit_sim(&sim, forks, NULL);
		return (1);
	}
	run_sim(&sim, philos);
	exit_sim(&sim, forks, philos);
	return (0);
}
