/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edepauw <edepauw@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 09:53:11 by edepauw           #+#    #+#             */
/*   Updated: 2021/05/01 18:41:54 by edepauw          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int	wait_fork(t_philos	*philos)
{
	struct timeval	now;

	while (philos->global->i_fork < 2)
	{
		gettimeofday(&now, NULL);
		checkdie(now, philos, 0);
		if (philos->global->stop)
			return (1);
	}
	return (0);
}

void	*routine(void *p_data)
{
	t_philos		*philos;
	struct timeval	start;

	philos = p_data;
	gettimeofday(&start, NULL);
	philos->last_eat = start;
	while (1)
	{
		if (wait_fork(philos))
			return (NULL);
		philo_eat(philos);
		if (philos->global->stop)
			break ;
		philo_sleep(philos);
		status(philos->id, "is thinking", philos->global, philos);
	}
	return (NULL);
}

int	ft_philo(int ac, char **av)
{
	t_init		init;
	pthread_t	*philo;
	pthread_t	check[1];
	t_philos	*philos;
	t_philos	checker[1];

	philo = (pthread_t *)malloc(sizeof(pthread_t) * ft_atoi(av[1]));
	philos = (t_philos *)malloc(sizeof(t_philos) * ft_atoi(av[1]));
	if (init_arg(&init, av, ac))
		return (1);
	if (init_all(init, philos, checker))
		return (1);
	ft_thread(philos, philo, checker, check);
	return (0);
}

int	main(int ac, char **av)
{
	if (check_arg(ac, av))
		return (1);
	return (ft_philo(ac, av));
}
