/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcoenon <bcoenon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 00:20:08 by bcoenon           #+#    #+#             */
/*   Updated: 2023/01/28 01:45:11 by bcoenon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	lock_forks(t_philo *phi)
{
	if (phi->thread_id % 2 == 0)
	{
		pthread_mutex_lock(&phi->left_fork);
		protect_print(phi->data, phi->thread_id, "has taken a fork");
		pthread_mutex_lock(phi->right_fork);
		protect_print(phi->data, phi->thread_id, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(phi->right_fork);
		protect_print(phi->data, phi->thread_id, "has taken a fork");
		pthread_mutex_lock(&phi->left_fork);
		protect_print(phi->data, phi->thread_id, "has taken a fork");
	}
}

void	unlock_forks(t_philo *phi)
{
	if (phi->thread_id % 2 == 0)
	{
		pthread_mutex_unlock(phi->right_fork);
		pthread_mutex_unlock(&phi->left_fork);
	}
	else
	{
		pthread_mutex_unlock(&phi->left_fork);
		pthread_mutex_unlock(phi->right_fork);
	}
}

int	ft_eat(t_philo *ari)
{
	if (ari->data->philo == 1)
	{
		pthread_mutex_lock(&ari->left_fork);
		protect_print(ari->data, ari->thread_id, "has taken a fork");
		ft_sleep(ari->time_to_die + 10);
		pthread_mutex_unlock(&ari->left_fork);
		return (0);
	}
	lock_forks(ari);
	protect_print(ari->data, ari->thread_id, "is eating");
	pthread_mutex_lock(&ari->eat);
	ari->last_eat = ft_clock();
	pthread_mutex_unlock(&ari->eat);
	ft_sleep(ari->time_to_eat);
	pthread_mutex_lock(&ari->lunches_p);
	ari->lunches++;
	pthread_mutex_unlock(&ari->lunches_p);
	unlock_forks(ari);
	return (0);
}

int	live(t_philo *ari)
{
	ft_eat(ari);
	if (ari->data->death == 0)
	{
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
	pthread_mutex_lock(&philo->data->lock);
	pthread_mutex_unlock(&philo->data->lock);
	pthread_mutex_lock(&philo->eat);
	philo->last_eat = ft_clock();
	pthread_mutex_unlock(&philo->eat);
	if (philo->thread_id % 2 == 1)
		usleep((philo->time_to_eat / 2) * 100);
	while (is_someone_dead(philo->data) == 0
		&& philo->lunches != philo->data->lunches)
	{
		live(philo);
	}
	return (arg);
}
