/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcoenon <bcoenon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 00:20:08 by bcoenon           #+#    #+#             */
/*   Updated: 2022/12/30 13:01:27 by bcoenon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_forks_pair(t_data *data, t_philo *ari)
{
	pthread_mutex_lock(&ari->fork);
	protect_print(data, ari->thread_id, "has taken a fork");
	if (data->philo == 1)
	{
		return (1);
	}
	else
	{
		if (ari->thread_id == 0 && data->philo != 1)
			pthread_mutex_lock(&data->ecclesia[data->philo - 1].fork);
		else if (data->philo != 1)
			pthread_mutex_lock(&data->ecclesia[ari->thread_id - 1].fork);
		protect_print(data, ari->thread_id, "has taken a fork");
	}
	return (0);
}

int	get_forks_impair(t_data *data, t_philo *ari)
{
	if (ari->thread_id == 0)
		pthread_mutex_lock(&data->ecclesia[data->philo - 1].fork);
	else
		pthread_mutex_lock(&data->ecclesia[ari->thread_id - 1].fork);
	protect_print(data, ari->thread_id, "has taken a fork");
	pthread_mutex_lock(&ari->fork);
	protect_print(data, ari->thread_id, "has taken a fork");
	return (0);
}

int	get_forks(t_data *data, t_philo *ari)
{
	if (ari->thread_id % 2 == 2)
	{
		return (get_forks_pair(data, ari));
	}
	else
	{
		return (get_forks_impair(data, ari));
	}
}

int	lunch(t_data *data, t_philo *ari)
{
	if (get_forks(data, ari) == 0 && is_someone_dead(data) == 0)
	{
		protect_print(data, ari->thread_id, "is eating");
		pthread_mutex_lock(&ari->eat);
		ari->last_eat = ft_clock(data);
		++ari->lunches;
		pthread_mutex_unlock(&ari->eat);
		while (ft_clock(data) - ari->last_eat <= ari->time_to_eat
			&& is_someone_dead(data) == 0)
			usleep(1);
	}
	else
	{
		pthread_mutex_unlock(&ari->fork);
		usleep(ari->time_to_die);
		return (1);
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
	if (lunch(data, ari) == 0 && is_someone_dead(data) == 0)
	{
		ari->sleep = ft_clock(data);
		protect_print(data, ari->thread_id, "is sleeping");
		while (ft_clock(data) - ari->sleep <= ari->time_to_sleep)
		{
			if (is_someone_dead(data) == 1)
				return (1);
		}
		protect_print(data, ari->thread_id, "is thinking");
	}
	return (0);
}
