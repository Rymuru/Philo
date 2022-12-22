/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcoenon <bcoenon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 17:29:20 by bcoenon           #+#    #+#             */
/*   Updated: 2022/12/22 02:32:08 by bcoenon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_arg(int ac, char **av)
{
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
	return (0);
}

int	main(int ac, char **av)
{
	pthread_t	*illiade;
	t_data		data;

	if (check_arg(ac, av) == 1)
	{
		return (1);
	}
	if (init_data(&data, av) == 1)
		return (1);
	illiade = malloc(data.philo * (sizeof(pthread_t)));
	if (!illiade)
	{
		free(data.ecclesia);
		return (1);
	}
	init_philos(&data);
	launch_threads(illiade, data);
	free(illiade);
	free(data.ecclesia);
	return (0);
}
