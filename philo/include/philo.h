/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcoenon <bcoenon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 18:52:16 by bcoenon           #+#    #+#             */
/*   Updated: 2023/01/30 19:27:58 by bcoenon          ###   ########.fr       */
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
	pthread_mutex_t	write;
	pthread_mutex_t	lock;
	pthread_mutex_t	watcher;
}	t_data;

typedef struct s_philo
{
	int				thread_id;
	int				lunches;
	t_data			*data;
	uint64_t		last_eat;
	uint64_t		sleep;
	uint64_t		time_to_eat;
	uint64_t		time_to_die;
	uint64_t		time_to_sleep;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	left_fork;
	pthread_mutex_t	lunches_p;
	pthread_mutex_t	eat;
}	t_philo;

uint64_t	ft_clock(void);
uint64_t	ft_atoi(char *str);

int			is_all_num(char **str);
int			init_data(t_data *data, char **av);
int			is_someone_dead(t_data *data);
int			check_death(t_data *data, t_philo *ari);
int			launch_threads(pthread_t *illiade, t_data *data, t_philo *ecclesia);

void		*routine(void *arg);
void		*ft_philo(void *data);
void		*init_philos(t_data *data);

void		ft_sleep(uint64_t delay);
void		ft_destroy(t_data *data, t_philo *ecclesia);
void		protect_print(t_data *data, int thread_id, char *str);

#endif