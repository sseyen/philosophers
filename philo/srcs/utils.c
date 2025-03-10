/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisseye <alisseye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 16:45:59 by alisseye          #+#    #+#             */
/*   Updated: 2025/03/10 15:13:59 by alisseye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

int	get_timestamp(struct timeval *start)
{
	struct timeval	now;
	int				ms;

	gettimeofday(&now, NULL);
	ms = ((now.tv_sec - start->tv_sec) * 1000) + \
		((now.tv_usec - start->tv_usec) / 1000);
	return (ms);
}

pthread_mutex_t	*init_forks(t_sim *sim)
{
	int				i;
	pthread_mutex_t	*forks;

	forks = malloc(sizeof(pthread_mutex_t) * sim->num_philo);
	if (!forks)
		printf("Error: failed to allocate memory for forks\n");
	i = 0;
	while (i < sim->num_philo)
	{
		if (pthread_mutex_init(&forks[i], NULL))
		{
			while (i >= 0)
				pthread_mutex_destroy(&forks[i--]);
			free(forks);
			printf("Error: failed to initialize forks\n");
		}
		i++;
	}
	return (forks);
}
