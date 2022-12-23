/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcoenon <bcoenon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 18:52:16 by bcoenon           #+#    #+#             */
/*   Updated: 2022/12/23 21:36:06 by bcoenon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdint.h>

typedef struct s_philo
{
	int				eat;
	int				thread_id;
	int				lunches;
	uint64_t		last_eat;
	uint64_t		sleep;
	pthread_mutex_t	fork;
}	t_philo;

typedef struct s_data
{
	int				philo;
	int				death;
	int				current;
	int				lunches;
	uint64_t		time_to_eat;
	uint64_t		time_to_die;
	uint64_t		time_to_sleep;
	t_philo			*ecclesia;
	pthread_mutex_t	write;
	pthread_mutex_t	lock;
}	t_data;

int			ft_atoi(char *str);
int			is_all_num(char **str);
int			init_data(t_data *data, char **av);
uint64_t	ft_clock(void);

void		live(t_data *data, t_philo *ari);
void		*ft_philo(void *data);
void		*routine(void *data);
void		init_philos(t_data *data);
void		launch_threads(pthread_t *illiade, t_data data);

#endif