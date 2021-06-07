/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edepauw <edepauw@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 09:53:11 by edepauw           #+#    #+#             */
/*   Updated: 2021/04/28 14:36:46 by edepauw          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int	wait_fork(t_philos	*philos)
{
	struct timeval	now;

	while (!philos->global->fork[philos->id - 1]
		|| !philos->global->fork[philos->next])
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
		philos->global->fork[philos->next] = 1;
		usleep(500);
		philos->global->fork[philos->id - 1] = 1;
		if (philos->global->stop)
			break ;
		philo_sleep(philos);
		status(philos->id, "is thinking", philos->global, philos);
	}
	return (NULL);
}

int	ft_free(t_philos *philos, pthread_t *philo)
{
	int i;

	i = -1;
	while (++i < philos[0].init.n_philo)
		free(philos[i].fork);
	if (philos[0].global->die != NULL)
		free(philos[0].global->die);
	if (philos[0].global->talk != NULL)
		free(philos[0].global->talk);
	if (philos[0].global->fork != NULL)
		free(philos[0].global->fork);
	if (philos[0].die)
		free(philos[0].global);
	if (philos[0].global)
		free(philos[0].global);
	if (philos != NULL)
		free(philos);
	if (philo != NULL)
		free(philo);
	return (0);
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
	ft_free(philos, philo);
	return (0);
}

int	main(int ac, char **av)
{
	if (check_arg(ac, av))
		return (1);
	return (ft_philo(ac, av));
}
