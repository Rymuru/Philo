/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcoenon <bcoenon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 00:20:08 by bcoenon           #+#    #+#             */
/*   Updated: 2023/01/24 15:28:47 by bcoenon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_eat(t_philo *ari)
{
	pthread_mutex_lock(&ari->left_fork);
	protect_print(ari->data, ari->thread_id, "has taken a fork");
	pthread_mutex_lock(ari->right_fork);
	protect_print(ari->data, ari->thread_id, "has taken a fork");
	protect_print(ari->data, ari->thread_id, "is eating");
	ari->last_eat = ft_clock();
	ft_sleep(ari->time_to_sleep);
	ari->lunches++;
	pthread_mutex_unlock(&ari->left_fork);
	pthread_mutex_unlock(ari->right_fork);
	return (0);
}

int	live(t_philo *ari)
{
	ft_eat(ari);
	if (ari->data->death == 0)
	{
		//ari->sleep = ft_clock();
		protect_print(ari->data, ari->thread_id, "is sleeping");
		ft_sleep(ari->time_to_sleep);
		protect_print(ari->data, ari->thread_id, "is thinking");
	}
	return (0);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->eat);
	philo->last_eat = ft_clock();
	pthread_mutex_unlock(&philo->eat);
	if (philo->thread_id % 2 == 1)
		usleep(philo->time_to_eat / 2);
	while (is_someone_dead(philo->data) == 0
		&& philo->lunches != philo->data->lunches)
	{
		live(philo);
	}
	return (arg);
}
