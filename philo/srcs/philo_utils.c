/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcoenon <bcoenon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 16:13:59 by bcoenon           #+#    #+#             */
/*   Updated: 2022/12/23 21:17:23 by bcoenon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

uint64_t	ft_clock(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
	{
		write(2, "Error: gettimeofday error.\n", 28);
		return (-1);
	}
	return ((tv.tv_usec / 1000) + (tv.tv_sec * 1000));
}
