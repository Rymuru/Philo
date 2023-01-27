/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcoenon <bcoenon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 23:15:46 by bcoenon           #+#    #+#             */
/*   Updated: 2023/01/27 19:03:58 by bcoenon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_right_fork(t_philo *ecclesia, int current)
{
	ecclesia[current].right_fork = &ecclesia[0].left_fork;
	--current;
	while (current >= 0)
	{
		ecclesia[current].right_fork = &ecclesia[current + 1].left_fork;
		--current;
	}
}

void	*init_philos(t_data *data)
{
	int		current;
	t_philo	*ecclesia;

	current = 0;
	ecclesia = malloc(data->philo * (sizeof(t_philo)));
	if (!ecclesia)
	{
		return (NULL);
	}
	while (current < data->philo)
	{
		ecclesia[current].time_to_die = data->time_to_die;
		ecclesia[current].time_to_eat = data->time_to_eat;
		ecclesia[current].time_to_sleep = data->time_to_sleep;
		ecclesia[current].thread_id = current;
		ecclesia[current].lunches = 0;
		ecclesia[current].data = data;
		pthread_mutex_init(&ecclesia[current].left_fork, NULL);
		pthread_mutex_init(&ecclesia[current].eat, NULL);
		pthread_mutex_init(&ecclesia[current].lunches_p, NULL);
		++current;
	}
	init_right_fork(ecclesia, current - 1);
	return (ecclesia);
}

int	init_data(t_data *data, char **av)
{
	data->death = 0;
	data->current = 0;
	if (av[1] == 0 || av[2] == 0 || av[3] == 0 || av[4] == 0)
		return (1);
	data->philo = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
	{
		if (av[5] == 0)
			return (1);
		data->lunches = ft_atoi(av[5]);
	}
	else
		data->lunches = -1;
	data->start = ft_clock();
	pthread_mutex_init(&data->lock, NULL);
	pthread_mutex_init(&data->write, NULL);
	pthread_mutex_init(&data->watcher, NULL);
	return (0);
}
