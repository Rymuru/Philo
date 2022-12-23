/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcoenon <bcoenon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 23:15:46 by bcoenon           #+#    #+#             */
/*   Updated: 2022/12/23 17:17:55 by bcoenon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philos(t_data *data)
{
	int	current;

	current = 0;
	while (current <= data->philo)
	{
		data->ecclesia[current].eat = 0;
		data->ecclesia[current].thread_id = current;
		data->ecclesia[current].lunches = 0;
		pthread_mutex_init(&data->ecclesia[current].fork, NULL);
		++current;
	}
}

int	init_data(t_data *data, char **av)
{
	data->death = 0;
	data->current = 0;
	data->philo = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		data->lunches = ft_atoi(av[5]);
	data->ecclesia = malloc(data->philo * (sizeof(t_philo)));
	if (!data->ecclesia)
	{
		return (1);
	}
	pthread_mutex_init(&data->write, NULL);
	pthread_mutex_init(&data->lock, NULL);
	return (0);
}
