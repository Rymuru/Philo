/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_threads.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcoenon <bcoenon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 23:18:29 by bcoenon           #+#    #+#             */
/*   Updated: 2023/01/24 22:42:51 by bcoenon          ###   ########.fr       */
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

void	launch_threads(pthread_t *illiade, t_data *data, t_philo *ecclesia)
{
	int	philo;

	philo = 0;
	while (philo < data->philo)
	{
		pthread_create(&illiade[philo], NULL, &routine, &ecclesia[philo]);
		++philo;
	}
	ft_sleep(data->time_to_die - 10);
	while (hades(data, ecclesia) != 1)
	{
		usleep(100);
	}
	philo = 0;
	while (philo < data->philo)
	{
		pthread_join(illiade[philo], NULL);
		++philo;
	}
}
