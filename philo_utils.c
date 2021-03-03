/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edepauw <edepauw@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 09:50:30 by edepauw           #+#    #+#             */
/*   Updated: 2021/03/03 10:56:19 by edepauw          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int		init_global(t_global *global, int n_philo)
{
	global = malloc(sizeof(t_global));
	global->fork = malloc(sizeof(int) * n_philo);
	global->stop = 0;
	if (!(global->talk = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t))))
		return (1);
	if (!(global->die = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t))))
		return (1);
	gettimeofday(&global->start, NULL);
	pthread_mutex_init(global->talk, NULL);
	return (0);
}

void	init_arg(t_init *init, char **av, int ac)
{
	init->n_philo = ft_atoi(av[1]);
	init->t_die = ft_atoi(av[2]);
	init->t_eat = ft_atoi(av[3]);
	init->t_sleep = ft_atoi(av[4]);
	if (ac == 6)
		init->n_eat = ft_atoi(av[5]);
}

int		init_philo(t_philos *philos, t_init *init, t_global *global, int id)
{
	philos->init = *init;
	philos->id = id;
	dprintf(1,"ici");
	if (init->n_philo == 1)
		global->fork[id] = 0;
	else
		global->fork[id] = 1;
	philos->global = global;
	philos->die = 0;
	if (!(philos->fork = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t))))
		return (1);
	pthread_mutex_init(philos->fork, NULL);
	return (0);
}

long	ft_conv_to_ms(struct timeval philo_time, struct timeval start_time)
{
	long	sec;
	long	micro;
	long	mili;

	sec = philo_time.tv_sec - start_time.tv_sec;
	micro = philo_time.tv_usec - start_time.tv_usec;
	mili = micro * 0.001 + sec * 1000;
	return (mili);
}

void	status(int id, char *str, t_global *global, t_philos *philos)
{
	struct timeval now;

	if (global->stop == 1)
		return ;
	if (philos->die == 1)
	{
		pthread_mutex_lock(global->talk);
		global->stop = 1;
		gettimeofday(&now, NULL);
		printf("%ld %d died\n", ft_conv_to_ms(now, global->start), id);
		pthread_mutex_unlock(global->talk);
		return ;
	}
	pthread_mutex_lock(global->talk);
	gettimeofday(&now, NULL);
	printf("%ld %d %s\n", ft_conv_to_ms(now, global->start), id, str);
	pthread_mutex_unlock(global->talk);
}
