/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisseye <alisseye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:20:27 by alisseye          #+#    #+#             */
/*   Updated: 2025/04/16 14:31:08 by alisseye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_atoi(const char *str)
{
	int	sign;
	int	result;

	result = 0;
	sign = 1;
	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -sign;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	return (result * sign);
}

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int	ft_isnumber(char *str)
{
	if (*str == '-' || *str == '+')
		str++;
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

int	parse_args(int argc, char **argv, t_sim *sim)
{
	if (argc < 5 || argc > 6)
		return (printf("Error: wrong number of arguments\n"), 0);
	if (!ft_isnumber(argv[1]) || !ft_isnumber(argv[2]) || !ft_isnumber(argv[3]) \
		|| !ft_isnumber(argv[4]) || (argc == 6 && !ft_isnumber(argv[5])))
		return (printf("Error: arguments must be positive numbers\n"), 0);
	sim->num_philo = ft_atoi(argv[1]);
	sim->time_to_die = ft_atoi(argv[2]);
	sim->time_to_eat = ft_atoi(argv[3]);
	sim->time_to_sleep = ft_atoi(argv[4]);
	sim->num_meals = -1;
	if (argc == 6)
		sim->num_meals = ft_atoi(argv[5]);
	if (sim->num_philo < 1 || sim->time_to_die < 1 || sim->time_to_eat < 1 \
		|| sim->time_to_sleep < 1 || sim->num_meals < -1)
		return (printf("Error: arguments must be positive numbers\n"), 0);
	return (1);
}
