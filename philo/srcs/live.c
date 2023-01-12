/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcoenon <bcoenon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 00:20:08 by bcoenon           #+#    #+#             */
/*   Updated: 2023/01/12 16:45:59 by bcoenon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	live(t_philo *ari)
{
	check_death(ari->data, ari);
	if (ari->thread_id % 2 == 0 != ari->lunches != 0)
		//lunch(data, ari);
	if (ari->data->death == 0)
	{
		ari->sleep = ft_clock();
		protect_print(ari->data, ari->thread_id, "is sleeping");
		while (ft_clock() - ari->sleep <= ari->data->time_to_sleep)
		{
			if (ft_clock() - ari->last_eat > ari->data->time_to_die)
				check_death(ari->data, ari);
		}
		protect_print(ari->data, ari->thread_id, "is thinking");
	}
	return (0);
}

void	*routine(void *arg)
{
	int		i;
	t_philo	*philo;

	philo = (t_philo *)arg;
	philo->last_eat = ft_clock();
	while (philo->data->death == 0 && philo->lunches != philo->data->lunches)
		live(philo);
 	philo->data->death = 1;
	return (arg);
}
