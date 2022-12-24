/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcoenon <bcoenon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 00:20:08 by bcoenon           #+#    #+#             */
/*   Updated: 2022/12/24 03:52:00 by bcoenon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	get_forks(t_data *data, t_philo *ari)
{
	pthread_mutex_lock(&ari->fork);
	protect_print(data, ari->thread_id, "has taken a fork");
	if (data->philo == 1)
	{
		usleep(data->time_to_die);
		protect_print(data, ari->thread_id, "died");
		data->death = 1;
	}
	else
	{
		if (ari->thread_id == 0 && data->philo != 1)
			pthread_mutex_lock(&data->ecclesia[data->philo - 1].fork);
		else if (data->philo != 1)
			pthread_mutex_lock(&data->ecclesia[ari->thread_id - 1].fork);
		protect_print(data, ari->thread_id, "has taken a fork");
	}
}

int	lunch(t_data *data, t_philo *ari)
{
	get_forks(data, ari);
	if (check_death(data, ari) == 0)
	{
		protect_print(data, ari->thread_id, "is eating");
		ari->last_eat = ft_clock();
		++ari->lunches;
		while (ft_clock() - ari->last_eat <= data->time_to_eat
			&& data->death == 0)
			check_death(data, ari);
	}
	pthread_mutex_unlock(&ari->fork);
	if (ari->thread_id == 0 && data->philo != 1)
		pthread_mutex_unlock(&data->ecclesia[data->philo - 1].fork);
	else if (data->philo != 1)
		pthread_mutex_unlock(&data->ecclesia[ari->thread_id - 1].fork);
	return (0);
}

int	live(t_data *data, t_philo *ari)
{
	check_death(data, ari);
	if (ari->thread_id % 2 == 0 != data->ecclesia[0].lunches != 0)
		lunch(data, ari);
	if (data->death == 0)
	{
		ari->sleep = ft_clock();
		protect_print(data, ari->thread_id, "is sleeping");
		while (ft_clock() - ari->sleep <= data->time_to_sleep)
		{
			if (ft_clock() - ari->last_eat > data->time_to_die)
				check_death(data, ari);
		}
		protect_print(data, ari->thread_id, "is thinking");
	}
	return (0);
}

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
	while (data->death == 0 && data->ecclesia[i].lunches != data->lunches)
		live(data, &data->ecclesia[i]);
	data->death = 1;
	return (arg);
}
