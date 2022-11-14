/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcoenon <bcoenon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 17:29:20 by bcoenon           #+#    #+#             */
/*   Updated: 2022/11/14 19:09:04 by bcoenon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

int	main(int ac, char **av)
{
	int		philo;
	t_philo	dio;

	if (ac != 5 || ac != 6)
		return (0);
	philo = ft_atoi(av[1]);
	dio.time_to_die = ft_atoi(av[2]);
	dio.time_to_eat = ft_atoi(av[3]);
	dio.time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		dio.lunches = ft_atoi(av[5]);
	while (philo > 0)
	{
		pthread_create();
		--philo;
	}
}

int	ft_atoi(char *str)
{
	int	i;
	int	nb;
	int	sign;

	i = 0;
	nb = 0;
	sign = 1;
	while (str[i] == ' ')
		++i;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		++i;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = nb * 10 + str[i] - '0';
		++i;
	}
	return (nb * sign);
}
