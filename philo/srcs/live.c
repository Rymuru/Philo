/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcoenon <bcoenon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 00:20:08 by bcoenon           #+#    #+#             */
/*   Updated: 2022/12/22 07:06:05 by bcoenon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*int	first_lunch(t_data *data, t_philo ari)
{
	if (ari.thread_id % 2 == 1)
	{
		pthread_mutex_lock(&ari.fork);
		pthread_mutex_lock(&data->ecclesia[ari.thread_id - 1].fork);
	}
	return (0);
}

void	live(t_data *data, t_philo ari)
{
	if (first_lunch(data, ari) == 1)
		data->death = 1; 
	while (data->death == 0)
	{
		while (ari.eat == 0)
		{
			ari.time = gettimeofday(&ari.tv, NULL);
			if (ari.time - ari.last_eat > data->time_to_die)
				data->death = 1;
			if (pthread_mutex_trylock(&data->ecclesia[ari.thread_id - 1].fork) == 0 &&
				pthread_mutex_trylock(&data->ecclesia[ari.thread_id + 1].fork) == 0)
				ari.eat = 1;
				
		}
	}
}*/

void	live(t_data *data, t_philo ari)
{
	pthread_mutex_lock(&data->write);
	printf("thread %d started", ari.thread_id);
	pthread_mutex_unlock(&data->write);
}

void *routine(void *arg)
{
	int		i;
	t_data *data;
	
	data = (t_data *)arg;
	pthread_mutex_lock(&data->lock);
	i = data->current;
	++data->current;
	pthread_mutex_unlock(&data->lock);
	live(data, data->ecclesia[i]);
	return (arg);
}
