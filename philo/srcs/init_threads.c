/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_threads.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcoenon <bcoenon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 23:18:29 by bcoenon           #+#    #+#             */
/*   Updated: 2022/12/24 03:22:35 by bcoenon          ###   ########.fr       */
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
		++philo;
	}
	--philo;
	while (data.death == 0)
	while (philo >= 0)
	{
		pthread_join(illiade[philo], NULL);
		--philo;
	}
}
