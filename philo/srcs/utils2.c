/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcoenon <bcoenon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 15:11:26 by bcoenon           #+#    #+#             */
/*   Updated: 2023/01/25 16:27:33 by bcoenon          ###   ########.fr       */
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
		data->death = 1;
		pthread_mutex_unlock(&data->watcher);
		pthread_mutex_lock(&data->write);
		printf("%lu %d %s\n", ft_clock() - data->start,
			ari->thread_id, "died");
		pthread_mutex_unlock(&data->write);
		return (1);
	}
	else
		pthread_mutex_unlock(&ari->eat);
	return (0);
}

int	is_someone_dead(t_data *data)
{
	pthread_mutex_lock(&data->watcher);
	if (data->death == 1)
	{
		pthread_mutex_unlock(&data->watcher);
		return (1);
	}
	pthread_mutex_unlock(&data->watcher);
	return (0);
}

void	ft_sleep(uint64_t delay)
{
	uint64_t	start;

	start = ft_clock();
	while (ft_clock() - start < delay)
		usleep(100);
}
