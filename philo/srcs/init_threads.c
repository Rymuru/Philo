/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_threads.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcoenon <bcoenon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 23:18:29 by bcoenon           #+#    #+#             */
/*   Updated: 2022/12/23 21:46:33 by bcoenon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	launch_threads(pthread_t *illiade, t_data data)
{
	int	philo;

	philo = 0;
	while (philo < data.philo)
	{
		pthread_create(&illiade[philo], NULL, &routine, &data);
		printf("%d created\n", philo);
		++philo;
	}
	while (philo >= 0)
	{
		pthread_join(illiade[philo], NULL);
		--philo;
	}
}

/*void	*ft_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->write);
	printf("philo created\n");
	pthread_mutex_unlock(&philo->write);
	sleep(3);
	pthread_mutex_lock(&philo->write);
	printf("philo died\n");
	pthread_mutex_unlock(&philo->write);
	return (arg);
}*/
