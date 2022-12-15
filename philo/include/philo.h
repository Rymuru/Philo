/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcoenon <bcoenon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 18:52:16 by bcoenon           #+#    #+#             */
/*   Updated: 2022/11/16 16:36:27 by bcoenon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	pthread_mutex_t	fork;
	pthread_mutex_t	death;
	pthread_mutex_t	write;
	int				time_to_eat;
	int				time_to_die;
	int				time_to_sleep;
	int				lunches;
	int				philo;
}	t_philo;

int	ft_atoi(char *str);
int	is_all_num(char **str);

#endif