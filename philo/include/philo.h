/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcoenon <bcoenon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 18:52:16 by bcoenon           #+#    #+#             */
/*   Updated: 2022/12/29 00:17:52 by bcoenon          ###   ########.fr       */
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
# include <limits.h>

typedef struct s_philo
{
	int				thread_id;
	int				lunches;
	uint64_t		last_eat;
	uint64_t		sleep;
	uint64_t		time_to_eat;
	uint64_t		time_to_die;
	uint64_t		time_to_sleep;
	pthread_mutex_t	fork;
	pthread_mutex_t eat;
}	t_philo;

typedef struct s_data
{
	int				philo;
	int				death;
	int				current;
	int				lunches;
	uint64_t		start;
	uint64_t		time_to_eat;
	uint64_t		time_to_die;
	uint64_t		time_to_sleep;
	t_philo			*ecclesia;
	pthread_mutex_t	lock;
	pthread_mutex_t	write;
	pthread_mutex_t	clock;
	pthread_mutex_t	watcher;
}	t_data;

uint64_t	ft_clock(t_data *data);
uint64_t	ft_atoi(char *str);
int			is_all_num(char **str);
int			is_someone_dead(t_data *data);
int			live(t_data *data, t_philo *ari);
int			init_data(t_data *data, char **av);
int			check_death(t_data *data, t_philo *ari);

void		*ft_philo(void *data);
void		*routine(void *data);
void		init_philos(t_data *data);
void		launch_threads(pthread_t *illiade, t_data data);
void		protect_print(t_data *data, int thread_id, char *str);

#endif