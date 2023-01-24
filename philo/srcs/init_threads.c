/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_threads.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcoenon <bcoenon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 23:18:29 by bcoenon           #+#    #+#             */
/*   Updated: 2023/01/24 14:32:06 by bcoenon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death(t_data *data, t_philo *ari)
{
	pthread_mutex_lock(&ari->eat);
	if (ft_clock() - ari->last_eat > data->time_to_die)
	{
		pthread_mutex_unlock(&ari->eat);
		pthread_mutex_lock(&data->watcher);
		pthread_mutex_lock(&data->write);
		printf("%lu %d %s\n", ft_clock() - data->start,
			ari->thread_id, "died");
		data->death = 1;
		pthread_mutex_unlock(&data->write);
		pthread_mutex_unlock(&data->watcher);
		return (1);
	}
	else
		pthread_mutex_unlock(&ari->eat);
	return (0);
}

int	hades(t_data *data, t_philo *ecclesia)
{
	int	i;

	i = 0;
	while (i < data->philo)
	{
		if (check_death(data, &ecclesia[i]) == 1)
			return (1);
		++i;
	}
	i = 0;
	return (0);
}

void	launch_threads(pthread_t *illiade, t_data *data, t_philo *ecclesia)
{
	int	philo;

	philo = 0;
	while (philo < data->philo)
	{
		pthread_create(&illiade[philo], NULL, &routine, &ecclesia[philo]);
		++philo;
	}
	while (hades(data, ecclesia) != 1)
	{
		usleep(500);
	}
	philo = 0;
	while (philo < data->philo)
	{
		pthread_join(illiade[philo], NULL);
		++philo;
	}
}
