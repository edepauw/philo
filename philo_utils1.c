/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edepauw <edepauw@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 10:04:53 by edepauw           #+#    #+#             */
/*   Updated: 2021/03/03 10:54:58 by edepauw          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int	init_all(t_init init, t_global *global, t_philos *philos)
{
	int i;

	if (init_global(global, init.n_philo))
		return (1);
	i = 0;
	while (i < init.n_philo)
	{		init_philo(&philos[i], &init, global, i + 1);
		i++;
	}
	i = -1;
	while (++i < init.n_philo)
	{
		if (i == 0)
		{
			philos[i].next_fork = philos[i + 1].fork;
			pthread_mutex_init(philos->fork, NULL);
		}
		else if (i == init.n_philo - 1)
			philos[i].next_fork = philos[0].fork;
		else
			philos[i].next_fork = philos[i + 1].fork;
	}
	return (0);
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
