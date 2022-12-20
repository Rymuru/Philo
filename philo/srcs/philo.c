/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcoenon <bcoenon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 17:29:20 by bcoenon           #+#    #+#             */
/*   Updated: 2022/12/20 21:21:41 by bcoenon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_philo(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->write);
	printf("philo created\n");
	pthread_mutex_unlock(&philo->write);
	sleep(3);
	pthread_mutex_lock(&philo->write);
	printf("philo died\n");
	pthread_mutex_unlock(&philo->write);
	return (arg);
}

void	init_philo(t_philo *ecclesia)
{

}

void init_dio(t_philo *dio, char **av)
{
	dio->philo = ft_atoi(av[1]);
	dio->time_to_die = ft_atoi(av[2]);
	dio->time_to_eat = ft_atoi(av[3]);
	dio->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		dio->lunches = ft_atoi(av[5]);
	pthread_mutex_init(&dio->write, NULL);
}

int	main(int ac, char **av)
{
	int			philo;
	pthread_t	*illiade;
	t_data		data;


	if (ac != 5 && ac != 6)
	{
		printf("invalid number of arguments\n");
		return (1);
	}
	if (is_all_num(av) == 1)
	{
		printf("not numbers\n");
		return (1);
	}
	init_dio(&data.dio, av);
	philo = ft_atoi(av[1]);
	illiade = malloc(philo * (sizeof(pthread_t)));
	data.ecclesia = malloc(philo * (sizeof(t_philo)));
	init_philo(data.ecclesia);
	while (philo > 0)
	{
		pthread_create(&illiade[philo], NULL, &ft_philo, &data);
		--philo;
	}
	while (philo <= data.dio.philo)
	{
		pthread_join(illiade[philo], NULL);
		++philo;
	}
	free(illiade);
	free(data.ecclesia);
	return (0);
}
