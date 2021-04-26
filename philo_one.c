/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edepauw <edepauw@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 09:53:11 by edepauw           #+#    #+#             */
/*   Updated: 2021/04/21 12:48:56 by edepauw          ###   ########lyon.fr   */
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

void	philo_eat(t_philos *philos)
{
	struct timeval now;
	struct timeval start;

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
	philos->last_eat = start;
	now = start;
	while (ft_conv_to_ms(now, start) < philos->init.t_eat)
	{
		usleep(100);
		checkdie(start, philos, 1);
		gettimeofday(&now, NULL);
	}
	philos->c_eat += 1;
	pthread_mutex_unlock(philos->fork);
	pthread_mutex_unlock(philos->next_fork);
}

void	philo_sleep(t_philos *philos)
{
	struct timeval now;
	struct timeval start;
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
	while(checker->global->stop == 0)
	{
		usleep(5000);
	}
	return (NULL);
}
void	*routine(void *p_data)
{
	t_philos		*philos;
	struct timeval	start;
	struct timeval	now;
	philos = p_data;
	gettimeofday(&start, NULL);
	philos->last_eat = start;
	while (1)
	{
		while (!philos->global->fork[philos->id - 1] //sa fourchette
				|| !philos->global->fork[philos->next])//fourchette suivante
		{
			//dprintf(1, "philo %d fork#%d =%d fork#%d =%d\n",philos->id,philos->id -1, philos->global->fork[philos->id - 1] ,philos->next, philos->global->fork[philos->next]);
			usleep(100);
			gettimeofday(&now, NULL);
			checkdie(now, philos, 0);
			if (philos->global->stop)
				return NULL;
		}
		philo_eat(philos);
		philos->global->fork[philos->id - 1] = 1;
		philos->global->fork[philos->next] = 1;
		if (philos->global->stop || philos->c_eat == philos->init.n_eat)
			break ;
		philo_sleep(philos);
		status(philos->id, "is thinking", philos->global, philos);
	}
	return (NULL);
}

int		main(int ac, char **av)
{
	t_init		init;
	int			i;
	pthread_t	philo[ft_atoi(av[1])];
	pthread_t	check[1];
	t_philos	philos[ft_atoi(av[1])];
	t_philos	checker[1];

	if (ac < 5 || ac > 6)
		return (1);
	init_arg(&init, av, ac);
	if (init_all(init, philos, checker))
		return (1);
	i = -1;
	while (++i < init.n_philo)
		pthread_create(&philo[i], NULL, routine, (void *)&philos[i]);
	pthread_create(&check[0], NULL, rt_checker, (void *)&checker[0]);
	pthread_join(check[0] , NULL);
	return (0);
}
