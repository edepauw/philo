/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edepauw <edepauw@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 09:53:11 by edepauw           #+#    #+#             */
/*   Updated: 2021/03/03 10:44:31 by edepauw          ###   ########lyon.fr   */
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
	philos->global->fork[philos->id] = 0;
	pthread_mutex_lock(philos->fork);
	status(philos->id, "has taken a fark", philos->global, philos);
	pthread_mutex_lock(philos->next_fork);
	status(philos->id, "has taken a fark", philos->global, philos);
	gettimeofday(&start, NULL);
	checkdie(start, philos, 1);
	if (philos->die == 1 || philos->global->stop == 1)
		return ;
	status(philos->id, "is eating", philos->global, philos);
	gettimeofday(&start, NULL);
	philos->last_eat = start;
	now = start;
	while (ft_conv_to_ms(now, start) < philos->init.t_eat)
	{
		usleep(50);
		gettimeofday(&now, NULL);
	}
	philos->c_eat += 1;
	philos->global->fork[philos->id] = 1;
	philos->global->fork[philos->id - 1] = 1;
}

void	philo_sleep(t_philos *philos)
{
	struct timeval now;
	struct timeval start;

	pthread_mutex_unlock(philos->fork);
	pthread_mutex_unlock(philos->next_fork);
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
		while (!philos->global->fork[philos->id - 1]
				|| !philos->global->fork[philos->id])
		{
			usleep(50);
			gettimeofday(&now, NULL);
			checkdie(now, philos, 0);
			if (philos->global->stop)
				break ;
		}
		philo_eat(philos);
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
	t_global	*global;
	pthread_t	philo[ft_atoi(av[1])];
	t_philos	philos[ft_atoi(av[1])];

	if (ac < 5 || ac > 6)
		return (1);
	init_arg(&init, av, ac);

	if (init_all(init, global, philos))
		return (1);
	i = -1;
	while (++i < init.n_philo)
		pthread_create(&philo[i], NULL, routine, (void *)&philos[i]);
	i = -1;
	while (++i < init.n_philo)
	{
		pthread_join(philo[i], NULL);
	}
	return (0);
}
