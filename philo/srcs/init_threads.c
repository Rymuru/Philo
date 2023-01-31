/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_threads.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcoenon <bcoenon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 23:18:29 by bcoenon           #+#    #+#             */
/*   Updated: 2023/01/31 14:06:43 by bcoenon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	hades(t_data *data, t_philo *ecclesia)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&ecclesia[i].lunches_p);
	while (ecclesia[i].lunches == data->lunches)
	{
		pthread_mutex_unlock(&ecclesia[i].lunches_p);
		++i;
		if (i == data->philo)
			return (1);
		pthread_mutex_lock(&ecclesia[i].lunches_p);
	}
	pthread_mutex_unlock(&ecclesia[i].lunches_p);
	i = 0;
	while (i < data->philo)
	{
		if (check_death(data, &ecclesia[i]) == 1)
			return (1);
		++i;
	}
	return (0);
}

int	close_threads(pthread_t *illiade, int current, int value, int sleep)
{
	usleep(sleep * 1000);
	while (current >= 0)
	{
		pthread_join(illiade[current], NULL);
		--current;
	}
	if (value == 1)
		write(2, "fail to create threads\n", 23);
	return (value);
}

int	launch_threads(pthread_t *illiade, t_data *data, t_philo *ecclesia)
{
	int	philo;

	philo = 0;
	pthread_mutex_lock(&data->lock);
	while (philo < data->philo)
	{
		if (pthread_create(&illiade[philo], NULL, &routine, &ecclesia[philo]))
		{
			data->death = 1;
			pthread_mutex_unlock(&data->lock);
			return (close_threads(illiade, philo - 1, 1,
					data->time_to_eat + data->time_to_sleep));
		}
		++philo;
	}
	data->start = ft_clock();
	pthread_mutex_unlock(&data->lock);
	ft_sleep(data->time_to_die - 10);
	while (hades(data, ecclesia) != 1)
	{
		usleep(100);
	}
	return (close_threads(illiade, philo - 1, 0,
			data->time_to_eat + data->time_to_sleep));
}
