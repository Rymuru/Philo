/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcoenon <bcoenon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 23:15:46 by bcoenon           #+#    #+#             */
/*   Updated: 2023/01/12 17:31:05 by bcoenon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*init_philos(t_data *data)
{
	int		current;
	t_philo	*ecclesia;

	current = 0;
	ecclesia = malloc(data->philo * (sizeof(t_philo)));
	if (!ecclesia)
	{
		return (1);
	}
	while (current < data->philo)
	{
		ecclesia[current].time_to_die = data->time_to_die;
		ecclesia[current].time_to_eat = data->time_to_eat;
		ecclesia[current].time_to_sleep = data->time_to_sleep;
		ecclesia[current].thread_id = current;
		ecclesia[current].lunches = 0;
		pthread_mutex_init(&ecclesia[current].fork, NULL);
		pthread_mutex_init(&ecclesia[current].eat, NULL);
		++current;
	}
	return (ecclesia);
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
	else
		data->lunches = -1;
	pthread_mutex_init(&data->lock, NULL);
	pthread_mutex_init(&data->write, NULL);
	pthread_mutex_init(&data->clock, NULL);
	pthread_mutex_init(&data->watcher, NULL);
	data->start = ft_clock(data);
	return (0);
}
