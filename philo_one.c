#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>
#include "libft/libft.h"

typedef struct	s_init
{
	int	n_philo;
	int	t_eat;
	int	t_die;
	int	t_sleep;
	int	n_eat;
}				t_init;

typedef struct	s_global
{
	int				stop;
	struct timeval	start;
	int				*fork;
	pthread_mutex_t	*talk;
	pthread_mutex_t	*die;

}				t_global;

typedef struct	s_philos
{
	t_init			init;
	int				id;
	int				c_eat;
	struct timeval	last_eat;
	int				die;
	t_global		*global;
	pthread_mutex_t	*fork;
	pthread_mutex_t	*next_fork;
}				t_philos;

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

void	checkdie(struct timeval now, t_philos *philos)
{
	if (ft_conv_to_ms(now, philos->last_eat) >= philos->init.t_die)
	{
		philos->die = 1;
		status(philos->id, "died", philos->global, philos);
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
	status(philos->id, "has taken a fork", philos->global, philos);
	pthread_mutex_lock(philos->next_fork);
	status(philos->id, "has taken a fork", philos->global, philos);
	gettimeofday(&start, NULL);
	checkdie(start, philos);
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
	pthread_mutex_unlock(philos->fork);
	philos->global->fork[philos->id] = 1;
	pthread_mutex_unlock(philos->next_fork);
	philos->global->fork[philos->id - 1] = 1;
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
		checkdie(now, philos);
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
	philos->c_eat = 0;
	while (1)
	{
		while (!philos->global->fork[philos->id - 1] 
				|| !philos->global->fork[philos->id])
		{
			usleep(50);
			gettimeofday(&now, NULL);
			checkdie(now, philos);
			if (philos->global->stop)
				break;
		}
		philo_eat(philos);
		if (philos->global->stop || philos->c_eat == philos->init.n_eat)
			break ;
		philo_sleep(philos);
		status(philos->id, "is thinking", philos->global, philos);
	}
	return (NULL);
}

void	initialyze(t_init *init, char **av, int ac)
{
	init->n_philo = ft_atoi(av[1]);
	init->t_die = ft_atoi(av[2]);
	init->t_eat = ft_atoi(av[3]);
	init->t_sleep = ft_atoi(av[4]);
	if (ac == 6)
		init->n_eat = ft_atoi(av[5]);
}

int init_philo(t_philos *philos, t_init init, t_global *global, int id)
{
	philos->init = init;
	philos->id = id;
	philos->global = global;
	philos->die = 0;
	if (!(philos->fork = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t) * 1)))
		return (0);
	pthread_mutex_init(philos->fork, NULL);
	return (0);
}

int	main(int ac, char **av)
{
	t_init		init;
	int			i;
	t_global	*global;
	pthread_t	philo[ft_atoi(av[1])];
	t_philos	philos[ft_atoi(av[1])];

	if (ac < 5 || ac > 6)
		return (1);
	initialyze(&init, av, ac);
	global = malloc(sizeof(t_global));
	global->fork = malloc(sizeof(int) * init.n_philo);
	global->stop = 0;
	if (!(global->talk = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t))))
				return (0);
	if (!(global->die = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t))))
		return (0);
	gettimeofday(&global->start, NULL);
	pthread_mutex_init(global->talk, NULL);
	i = -1;
	while (++i < init.n_philo)
	{
		global->fork[i] = 1;
		init_philo(&philos[i], init, global, i + 1);
	}
	if (init.n_philo == 1)
		philos[0].die = 1;
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
	i = -1;
	while (++i < init.n_philo)
		pthread_create(&philo[i], NULL, routine, (void *)&philos[i]);
	i = -1;
	while (++i < init.n_philo)
	{
		pthread_join(philo[i], NULL);
	}
	return 0;
}
