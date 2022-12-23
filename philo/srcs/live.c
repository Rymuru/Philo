/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcoenon <bcoenon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 00:20:08 by bcoenon           #+#    #+#             */
/*   Updated: 2022/12/23 22:43:57 by bcoenon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_data *data, t_philo *ari)
{
	pthread_mutex_lock(&data->write);
	printf("%lu %d has taken a fork\n", ft_clock(), ari->thread_id);
	printf("%lu %d has taken a fork\n", ft_clock(), ari->thread_id);
	printf("%lu %d is eating\n", ft_clock(), ari->thread_id);
	pthread_mutex_unlock(&data->write);
	ari->last_eat = ft_clock();
	ari->eat = 1;
	while (ft_clock() - ari->last_eat <= data->time_to_eat
		&& data->death == 0)
	{
		if (ft_clock() - ari->last_eat > data->time_to_die)
			data->death = 1;
	}
}

int	lunch(t_data *data, t_philo *ari)
{
	int	back;

	back = 0;
	if (pthread_mutex_trylock(&ari->fork) == 1)
	{
		if (ari->thread_id != 0)
		{
			if (pthread_mutex_trylock(&data->ecclesia[ari->thread_id - 1].fork))
			{
				eat(data, ari);
				pthread_mutex_unlock(&data->ecclesia[ari->thread_id - 1].fork);
			}
		}
		else
		{
			if (pthread_mutex_trylock(&data->ecclesia[data->philo - 1].fork))
			{
				back = 1;
				eat(data, ari);
				pthread_mutex_unlock(&data->ecclesia[data->philo - 1].fork);
			}
		}
		pthread_mutex_unlock(&ari->fork);
	}
	return (0);
}

void	live(t_data *data, t_philo *ari)
{
	if (ft_clock() - ari->last_eat > data->time_to_die)
		data->death = 1;
	if (lunch(data, ari) == 1)
	{
		ari->sleep = ft_clock();
		pthread_mutex_lock(&data->write);
		printf("%lu %d is sleeping\n", ft_clock(), ari->thread_id);
		pthread_mutex_unlock(&data->write);
		while (ft_clock() - ari->sleep <= data->time_to_sleep
			&& data->current == 0)
		{
			if (ft_clock() - ari->last_eat > data->time_to_die)
				data->death = 1;
		}
		pthread_mutex_lock(&data->write);
		printf("%lu %d is thinking\n", ft_clock(), ari->thread_id);
		pthread_mutex_unlock(&data->write);
	}
}

/*void	live(t_data *data, t_philo *ari)
{
	pthread_mutex_lock(&data->write);
	printf("thread %d started\n", ari->thread_id);
	pthread_mutex_unlock(&data->write);
	data->death = 1;
}*/

void	*routine(void *arg)
{
	int		i;
	t_data	*data;

	data = (t_data *)arg;
	pthread_mutex_lock(&data->lock);
	i = data->current;
	++data->current;
	pthread_mutex_unlock(&data->lock);
	data->ecclesia[i].last_eat = ft_clock();
	while (data->death == 0)
		live(data, &data->ecclesia[i]);
	return (arg);
}
