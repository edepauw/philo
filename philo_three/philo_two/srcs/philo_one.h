#ifndef PHILO_ONE_H
# define PHILO_ONE_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <semaphore.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <semaphore.h>
# include <sys/time.h>

typedef struct s_init
{
	int	n_philo;
	int	t_eat;
	int	t_die;
	int	t_sleep;
	int	n_eat;
}				t_init;

typedef struct s_global
{
	int				stop;
	int				n_finish;
	int				i_fork;
	struct timeval	start;
	sem_t			*forks;
	sem_t			*talk;
	sem_t			*die;

}				t_global;

typedef struct s_philos
{
	t_init			init;
	int				id;
	int				next;
	int				c_eat;
	struct timeval	last_eat;
	int				die;
	t_global		*global;
}				t_philos;

long	ft_conv_to_ms(struct timeval philo_time, struct timeval start_time);
int		init_arg(t_init *init, char **av, int ac);
void	*routine(void *p_data);
void	*rt_checker(void *p_data);
void	philo_eat(t_philos *philos);
void	checkdie(struct timeval now, t_philos *philos, int eat);
void	philo_sleep(t_philos *philos);
void	ft_thread(t_philos *ps, pthread_t *p, t_philos *cr, pthread_t *c);
int		check_arg(int ac, char **av);
int		init_philo(t_philos *philos, t_init init, t_global *global, int id);
void	status(int id, char *str, t_global *global, t_philos *philos);
int		ft_atoi(const char *str);
int		init_global(t_global *global, int n_philo);
int		init_all(t_init init, t_philos *philos, t_philos *checker);

#endif
