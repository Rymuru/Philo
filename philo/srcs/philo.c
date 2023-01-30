/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcoenon <bcoenon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 17:29:20 by bcoenon           #+#    #+#             */
/*   Updated: 2023/01/30 19:53:41 by bcoenon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	error_manager(int error)
{
	if (error == 1)
		write(2, "shouldn't use 0 as parameter\n", 30);
	else if (error == 2)
		write(2, "can't malloc philo\n", 20);
	else if (error == 3)
		write(2, "can't malloc threads\n", 22);
	return (1);
}

int	check_arg(int ac, char **av)
{
	int	i;

	i = 1;
	if (ac != 5 && ac != 6)
	{
		write(2, "invalid number of arguments\n", 29);
		return (1);
	}
	if (is_all_num(av) == 1)
	{
		write(2, "not numbers\n", 13);
		return (1);
	}
	if (ft_atoi(av[i]) == 0)
		return (1);
	while (av[i])
	{
		if (ft_atoi(av[i]) > 2147483647)
			return (1);
		++i;
	}
	return (0);
}

int	main(int ac, char **av)
{
	pthread_t	*illiade;
	t_data		data;
	t_philo		*ecclesia;

	if (check_arg(ac, av) == 1)
		return (1);
	if (init_data(&data, av) == 1)
		return (error_manager(1));
	ecclesia = init_philos(&data);
	if (ecclesia == NULL)
		return (error_manager(2));
	illiade = malloc(data.philo * (sizeof(pthread_t)));
	if (!illiade)
	{
		free(ecclesia);
		return (error_manager(3));
	}
	launch_threads(illiade, &data, ecclesia);
	ft_destroy(&data, ecclesia);
	free(illiade);
	free(ecclesia);
	return (0);
}
