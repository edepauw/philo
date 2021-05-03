/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edepauw <edepauw@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 13:44:06 by edepauw           #+#    #+#             */
/*   Updated: 2021/05/03 11:55:18 by edepauw          ###   ########lyon.fr   */
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
			philos->global->i_fork++;
			sem_post(philos->global->forks);
			usleep(500);
			philos->global->i_fork++;
			sem_post(philos->global->forks);
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

	sem_wait(philos->global->forks);
	philos->global->i_fork--;
	status(philos->id, "has taken a fork", philos->global, philos);
	sem_wait(philos->global->forks);
	philos->global->i_fork--;
	status(philos->id, "has taken a fork", philos->global, philos);
	gettimeofday(&start, NULL);
	checkdie(start, philos, 1);
	status(philos->id, "is eating", philos->global, philos);
	gettimeofday(&start, NULL);
	wait_eat(philos, start);
	philos->c_eat += 1;
	dprintf(1, "[%d]n_eat = %d finish = %d\n",philos->id, philos->c_eat,philos->global->n_finish);
	if (philos->c_eat == philos->init.n_eat)
		sem_post();
	philos->global->i_fork++;
	sem_post(philos->global->forks);
	usleep(500);
	philos->global->i_fork++;
	sem_post(philos->global->forks);
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

void	*check_eat(void *p_data)
{
	t_philos		*checker;
	int i;

	checker = p_data;
	while (i < checker->init.n_philo)
	{
		sem_wait(checker->global->c_eat);
		i++;
	}
	return (NULL);
}

void	*rt_checker(void *p_data)
{
	t_philos		*checker;
	int i;

	checker = p_data;
	sem_wait(checker->global->die);
	return (NULL);
}
