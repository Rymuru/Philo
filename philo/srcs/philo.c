/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcoenon <bcoenon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 17:29:20 by bcoenon           #+#    #+#             */
/*   Updated: 2023/01/24 14:31:33 by bcoenon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_arg(int ac, char **av)
{
	int	i;

	i = 1;
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
	{
		return (1);
	}
	if (init_data(&data, av) == 1)
		return (1);
	ecclesia = init_philos(&data);
	illiade = malloc(data.philo * (sizeof(pthread_t)));
	if (!illiade)
	{
		free(ecclesia);
		return (1);
	}
	launch_threads(illiade, &data, ecclesia);
	free(illiade);
	free(ecclesia);
	return (0);
}
