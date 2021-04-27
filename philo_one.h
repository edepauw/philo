#ifndef PHILO_ONE_H
#define PHILO_ONE_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>

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
	int				n_finish;
	struct timeval	start;
	int				*fork;
	pthread_mutex_t	*talk;
	pthread_mutex_t	*die;

}				t_global;

typedef struct	s_philos
{
	t_init			init;
	int				id;
	int				next;
	int				c_eat;
	struct timeval	last_eat;
	int				die;
	t_global		*global;
	pthread_mutex_t	*fork;
	pthread_mutex_t	*next_fork;
}				t_philos;

long	ft_conv_to_ms(struct timeval philo_time, struct timeval start_time);
void	init_arg(t_init *init, char **av, int ac);
int init_philo(t_philos *philos, t_init init, t_global *global, int id);
void	status(int id, char *str, t_global *global, t_philos *philos);
int	ft_atoi(const char *str);
int		init_global(t_global *global, int n_philo);
int init_all(t_init init, t_philos *philos, t_philos *checker);

#endif
