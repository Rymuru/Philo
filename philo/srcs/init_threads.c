/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_threads.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcoenon <bcoenon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 23:18:29 by bcoenon           #+#    #+#             */
/*   Updated: 2023/01/12 17:37:37 by bcoenon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death(t_data *data, t_philo *ari)
{
	pthread_mutex_lock(&ari->eat);
	if (ft_clock(data) - ari->last_eat > data->time_to_die)
	{
		pthread_mutex_unlock(&ari->eat);
		pthread_mutex_lock(&data->watcher);
		pthread_mutex_lock(&data->write);
		printf("%lu %d %s\n", ft_clock(data) - data->start,
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

int	hades(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo)
	{
		if (check_death(data, &data->ecclesia[i]) == 1)
			return (1);
		++i;
	}
	i = 0;
	return (0);
}

void	*routine(void *arg)
{
	int		i;
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->eat);
	philo->last_eat = ft_clock(&philo->data);
	pthread_mutex_unlock(&philo->eat);
	while (is_someone_dead(philo->data) == 0
		&& philo->lunches != philo->data->lunches)
	{
		live(philo->data, philo);
	}
	return (arg);
}

void	launch_threads(pthread_t *illiade, t_data data, t_philo *ecclesia)
{
	int	philo;

	philo = 0;
	while (philo < data.philo)
	{
		pthread_create(&illiade[philo], NULL, &routine, &data);
		philo += 2;
	}
	usleep (200);
	philo = 1;
	while (philo < data.philo)
	{
		pthread_create(&illiade[philo], NULL, &routine, &data);
		philo += 2;
	}
	while (hades(&data) != 1)
	{
		usleep(500);
	}
	philo = 0;
	while (philo < data.philo)
	{
		pthread_join(illiade[philo], NULL);
		++philo;
	}
}
