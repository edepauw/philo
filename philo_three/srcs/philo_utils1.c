/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edepauw <edepauw@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 10:04:53 by edepauw           #+#    #+#             */
/*   Updated: 2021/05/03 11:52:18 by edepauw          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int	check_arg(int ac, char **av)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	if (ac < 5 || ac > 6)
		return (1);
	while (i < ac)
	{
		while (av[i][j])
		{
			if (av[i][j] < '0' || av[i][j] > '9')
				return (1);
			j++;
		}
		j = 0;
		i++;
	}
	return (0);
}

int	init_all(t_init init, t_philos *philos, t_philos *checker)
{
	int			i;
	t_global	*global;

	global = malloc(sizeof(t_global));
	if (!global)
		return (1);
	if (init_global(global, init.n_philo))
		return (1);
	i = -1;
	checker->global = global;
	checker->init.n_philo = init.n_philo;
	while (++i < init.n_philo)
		init_philo(&philos[i], init, global, i + 1);
	return (0);
}

void	ft_fork(t_philos *ps, t_philos *cr, pthread_t *c)
{
	int	i;
	pid_t pid;

	i = -1;
	// pid = (pid_t *)malloc(sizeof(pid_t) * ps->init.n_philo);
	while (++i < ps->init.n_philo && pid != 0)
	{
		pid = fork();
		if (pid == 0)
		{
			routine(&ps[i]);
		}
		// pthread_create(&p[i], NULL, routine, (void *)&ps[i]);
		// usleep(100);
	}
	if (pid != 0)
	{
		pthread_create(&c[0], NULL, rt_checker, (void *)&cr[0]);
		pthread_join(c[0], NULL);
	}
}

int	ft_atoi(const char *str)
{
	int					i;
	int					signe;
	unsigned long int	nb;
	char				*s;

	i = 0;
	signe = 1;
	nb = 0;
	s = (char *)str;
	while ((str[i] <= 13 && str[i] >= 9) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
		{
			signe = signe * -1;
			i++;
		}
		if (str[i] == '+' && signe > 0)
			i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
		nb = nb * 10 + str[i++] - 48;
	return (nb * signe);
}
