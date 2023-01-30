/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcoenon <bcoenon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 23:15:46 by bcoenon           #+#    #+#             */
/*   Updated: 2023/01/30 20:31:03 by bcoenon          ###   ########.fr       */
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

int	init_philo_mutex(t_philo *ari, t_data *data)
{
	int	value;

	value = 0;
	if (pthread_mutex_init(&ari->left_fork, NULL) == 1)
		value = 1;
	if (pthread_mutex_init(&ari->eat, NULL) == 1)
	{
		pthread_mutex_destroy(&ari->left_fork);
		value = 1;
	}
	if (pthread_mutex_init(&ari->lunches_p, NULL) == 1)
	{
		pthread_mutex_destroy(&ari->left_fork);
		pthread_mutex_destroy(&ari->eat);
		value = 1;
	}
	if (value == 1)
	{
		pthread_mutex_destroy(&data->lock);
		pthread_mutex_destroy(&data->write);
		pthread_mutex_destroy(&data->watcher);
	}
	return (0);
}

void	*init_philos(t_data *data)
{
	int		current;
	t_philo	*ecclesia;

	current = 0;
	ecclesia = malloc(data->philo * (sizeof(t_philo)));
	if (!ecclesia)
		return (NULL);
	while (current < data->philo)
	{
		ecclesia[current].time_to_die = data->time_to_die;
		ecclesia[current].time_to_eat = data->time_to_eat;
		ecclesia[current].time_to_sleep = data->time_to_sleep;
		ecclesia[current].thread_id = current + 1;
		ecclesia[current].lunches = 0;
		ecclesia[current].data = data;
		if (init_philo_mutex(&ecclesia[current], data) == 1)
		{
			free(ecclesia);
			return (NULL);
		}
		++current;
	}
	init_right_fork(ecclesia, current - 1);
	return (ecclesia);
}

int	init_data_mutex(t_data *data)
{
	if (pthread_mutex_init(&data->lock, NULL) == 1)
		return (1);
	if (pthread_mutex_init(&data->write, NULL) == 1)
	{
		pthread_mutex_destroy(&data->lock);
		return (1);
	}
	if (pthread_mutex_init(&data->watcher, NULL) == 1)
	{
		pthread_mutex_destroy(&data->lock);
		pthread_mutex_destroy(&data->write);
		return (1);
	}
	return (0);
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
	if (data->philo == 0 || data->time_to_die == 0 || data->time_to_eat == 0
		|| data->time_to_sleep == 0 || data->lunches == 0)
		return (1);
	if (init_data_mutex(data) == 1)
		return (1);
	return (0);
}
