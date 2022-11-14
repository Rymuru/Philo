/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcoenon <bcoenon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 18:52:16 by bcoenon           #+#    #+#             */
/*   Updated: 2022/11/14 19:05:39 by bcoenon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct s_philo
{
	pthread_mutex_t	fork;
	int				time_to_eat;
	int				time_to_die;
	int				time_to_sleep;
	int				lunches;
}	t_philo;

#endif