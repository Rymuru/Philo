/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcoenon <bcoenon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 16:13:59 by bcoenon           #+#    #+#             */
/*   Updated: 2022/12/29 00:21:09 by bcoenon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

uint64_t	ft_atoi(char *str)
{
	int			i;
	int			sign;
	uint64_t	nb;

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

int	is_all_num(char **str)
{
	int	line;
	int	letter;

	line = 1;
	while (str[line])
	{
		letter = 0;
		while (str[line][letter])
		{
			if (!(str[line][letter] >= '0' && str[line][letter] <= '9'))
				return (1);
			++letter;
		}
		++line;
	}
	return (0);
}

uint64_t	ft_clock(t_data *data)
{
	struct timeval	tv;

	pthread_mutex_lock(&data->clock);
	if (gettimeofday(&tv, NULL) == -1)
	{
		pthread_mutex_unlock(&data->clock);
		write(2, "Error: gettimeofday error.\n", 28);
		return (-1);
	}
	pthread_mutex_unlock(&data->clock);
	return ((tv.tv_usec / 1000) + (tv.tv_sec * 1000));
}

void	protect_print(t_data *data, int thread_id, char *str)
{
	pthread_mutex_lock(&data->write);
	if (is_someone_dead(data) == 0)
		printf("%lu %d %s\n", ft_clock(data) - data->start, thread_id, str);
	pthread_mutex_unlock(&data->write);
}

int	is_someone_dead(t_data *data)
{
	pthread_mutex_lock(&data->watcher);
	if (data->death == 1)
	{
		pthread_mutex_unlock(&data->watcher);
		return (1);
	}
	pthread_mutex_unlock(&data->watcher);
	return (0);
}
