/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edepauw <edepauw@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 13:44:06 by edepauw           #+#    #+#             */
/*   Updated: 2021/06/09 13:01:15 by edepauw          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	checkdie(struct timeval now, t_philos *philos, int eat)
{
	if (ft_conv_to_ms(now, philos->last_eat) >= philos->init.t_die)
	{
		philos->die = 1;
		status(philos->id, "died", philos->global, philos);
		if (eat)
		{
			pthread_mutex_unlock(philos->fork);
			pthread_mutex_unlock(philos->next_fork);
		}
		return ;
	}
}

void	wait_eat(t_philos *philos, struct timeval start)
{
	struct timeval	now;

	philos->last_eat = start;
	now = start;
	while (ft_conv_to_ms(now, start) < philos->init.t_eat)
	{
		usleep(100);
		checkdie(start, philos, 1);
		gettimeofday(&now, NULL);
	}
}

void	philo_eat(t_philos *philos)
{
	struct timeval	start;

	philos->global->fork[philos->id - 1] = 0;
	philos->global->fork[philos->next] = 0;
	pthread_mutex_lock(philos->fork);
	status(philos->id, "has taken a fork", philos->global, philos);
	pthread_mutex_lock(philos->next_fork);
	status(philos->id, "has taken a fork", philos->global, philos);
	gettimeofday(&start, NULL);
	checkdie(start, philos, 1);
	status(philos->id, "is eating", philos->global, philos);
	gettimeofday(&start, NULL);
	wait_eat(philos, start);
	philos->c_eat += 1;
	if (philos->c_eat == philos->init.n_eat)
		philos->global->n_finish++;
	pthread_mutex_unlock(philos->fork);
	usleep(50);
	pthread_mutex_unlock(philos->next_fork);
}

void	philo_sleep(t_philos *philos)
{
	struct timeval	now;
	struct timeval	start;

	status(philos->id, "is sleeping", philos->global, philos);
	gettimeofday(&start, NULL);
	while (1)
	{
		usleep(50);
		gettimeofday(&now, NULL);
		checkdie(now, philos, 0);
		if (ft_conv_to_ms(now, start) >= philos->init.t_sleep)
			break ;
	}
}

void	*rt_checker(void *p_data)
{
	t_philos		*checker;

	checker = p_data;
	while (checker->global->stop == 0)
	{
		if (checker->global->n_finish == checker->init.n_philo)
		{
			checker->global->stop = 1;
			pthread_mutex_lock(checker->global->talk);
			return (NULL);
		}
		usleep(100);
	}
	return (NULL);
}
