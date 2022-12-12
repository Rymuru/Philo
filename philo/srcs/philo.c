/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcoenon <bcoenon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 17:29:20 by bcoenon           #+#    #+#             */
/*   Updated: 2022/11/18 17:02:56 by bcoenon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_philo(void *dio)
{
	printf("philo created\n");
	sleep(3);
	printf("philo died\n");
}

void	*create_philo(t_philo dio)
{

}

t_philo init_dio(char *nb_philo, char *die, char *eat, char *sleep)
{
	t_philo dio;

	dio.philo = ft_atoi(nb_philo);
	dio.time_to_die = ft_atoi(die);
	dio.time_to_eat = ft_atoi(eat);
	dio.time_to_sleep = ft_atoi(sleep);

	return (dio);
}

int	main(int ac, char **av)
{.
	int		philo;
	char	*ecclesia;
	t_philo	dio;

	if (ac != 5 || ac != 6)
		return (0);
	dio = init_dio(av[1], av[2], av[3], av[4]);
	philo = ft_atoi(av[1]);
	if (av[5])
		dio.lunches = ft_atoi(av[5]);
	ecclesia = malloc(philo * (sizeof(t_philo)));
	while (philo > 0)
	{
		pthread_create(&ecclesia, NULL, &create_philo, &dio);
		--philo;
	}
	//while (philo <= dio.philo)
	//{
	//	pthread_join()
	//}
}
