/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edepauw <edepauw@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 09:50:30 by edepauw           #+#    #+#             */
/*   Updated: 2021/05/01 18:35:30 by edepauw          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int	init_global(t_global *global, int n_philo)
{
	int	i;

	i = 0;
	global->n_finish = 0;
	global->forks = sem_open("/forks", O_CREAT | O_EXCL, 0644, n_philo);
	sem_unlink("/forks");
	global->i_fork = n_philo;
	global->stop = 0;
	global->talk = sem_open("/talk", O_CREAT | O_EXCL, 0644, 1);
	sem_unlink("/talk");
	global->die = sem_open("/die", O_CREAT | O_EXCL, 0644, 0);
	sem_unlink("/die");
	if (global->forks == SEM_FAILED || global->talk == SEM_FAILED
		|| global->die == SEM_FAILED)
	{
		perror("sem_open failed");
		exit(EXIT_FAILURE);
	}
	gettimeofday(&global->start, NULL);
	return (0);
}

int	init_arg(t_init *init, char **av, int ac)
{
	init->n_philo = ft_atoi(av[1]);
	if (init->n_philo < 1)
		return (1);
	init->t_die = ft_atoi(av[2]);
	if (init->t_die < 0)
		return (1);
	init->t_eat = ft_atoi(av[3]);
	if (init->t_eat < 0)
		return (1);
	init->t_sleep = ft_atoi(av[4]);
	if (init->t_sleep < 0)
		return (1);
	if (ac == 6)
		init->n_eat = ft_atoi(av[5]);
	return (0);
}

int	init_philo(t_philos *philos, t_init init, t_global *global, int id)
{
	philos->init = init;
	philos->id = id;
	if (id == init.n_philo)
		philos->next = 0;
	else
		philos->next = id;
	philos->global = global;
	philos->die = 0;
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
	struct timeval	now;

	if (global->stop == 1)
		return ;
	if (philos->die == 1)
	{
		sem_wait(global->talk);
		global->stop = 1;
		gettimeofday(&now, NULL);
		printf("%ld %d died\n", ft_conv_to_ms(now, global->start), id);
		return ;
	}
	sem_wait(global->talk);
	gettimeofday(&now, NULL);
	printf("%ld %d %s\n", ft_conv_to_ms(now, global->start), id, str);
	sem_post(global->talk);
}
