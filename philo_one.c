#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  //Header file for sleep(). man 3 sleep for details.
#include <pthread.h>
#include <sys/time.h>
#include "libft/libft.h"
// A normal C function that is executed as a thread
// when its name is specified in pthread_create()
typedef struct  s_init
{
    int n_philo;
    int t_eat;
    int t_die;
    int t_sleep;
    int n_eat;
}               t_init;

typedef struct  s_table
{
    t_init init;
    int stop;
    int *i_fork;
    pthread_mutex_t *fork;
    pthread_mutex_t *talk;
    pthread_mutex_t *next_fork;
}               t_table;

typedef struct  s_philos
{
    t_init init;
    int id;
    long last_eat;
    struct s_table *table;
}               t_philos;

void status(int id, char *str, pthread_mutex_t *talk)
{

    struct timeval now;
    gettimeofday(&now, NULL);
    pthread_mutex_lock (talk);
    dprintf(1, "%d %d %s\n", now.tv_usec, id, str);
    pthread_mutex_unlock (talk);
}

void *routine(void *p_data)
{
    t_philos *philos;
    struct timeval start;
    philos = p_data;
    gettimeofday(&start, NULL);
    if(philos->id == philos->init.n_philo)
        philos->id = -1;
    while (1)
    {
        usleep(start.tv_usec % 200);
        philos->last_eat = start.tv_usec;
        if (philos->table->stop)
            return NULL;
        while (!philos->table->i_fork[philos->id] || !philos->table->i_fork[philos->id + 1])
        {
        }
        dprintf(1,"philo :%d, table->i_fork: %d, next_fork: %d",philos->id ,philos->table->i_fork[philos->id], philos->table->i_fork[philos->id + 1]);
        philos->table->i_fork[philos->id] = 0;
        pthread_mutex_lock (philos->table->next_fork);
        status(philos->id, "has taken a fork", philos->table->talk);
        philos->table->i_fork[philos->id + 1] = 0;
        pthread_mutex_lock (philos->table->fork);
        status(philos->id, "has taken a fork", philos->table->talk);
        gettimeofday(&start, NULL);
        if(start.tv_usec  - philos->last_eat  > philos->init.t_die *1000)
        {
            status(philos->id, "died", philos->table->talk);
            philos->table->stop = 1;
            return NULL;//die
        }
        if(philos->table->stop)
            return NULL;
        status(philos->id, "is eating", philos->table->talk);
        usleep(philos->init.t_eat * 1000);
        if(philos->table->stop)
            return NULL;
        pthread_mutex_unlock (philos->table->fork);
        philos->table->i_fork[philos->id] = 1;
        pthread_mutex_unlock (philos->table->next_fork);
        philos->table->i_fork[philos->id + 1] = 1;
        if(philos->table->stop)
            return NULL;
        status(philos->id, "is sleeping", philos->table->talk);
        usleep(philos->init.t_sleep * 1000);
        status(philos->id, "is thinking", philos->table->talk);
    }
    return NULL;
}

void initialyze(t_init *init, char **av, int ac)
{
    init->n_philo = ft_atoi(av[1]);
    init->t_die = ft_atoi(av[2]);
    init->t_eat = ft_atoi(av[3]);
    init->t_sleep = ft_atoi(av[4]);
    if (ac == 6)
        init->n_eat = ft_atoi(av[5]);
}

int init_philo(t_philos *philos, t_init init, int id)
{
    philos->init = init;
    philos->id = id;
    philos->table->i_fork[id] = 1;
    pthread_mutex_init(philos->table->fork, NULL);
    return (0);
}

int main(int ac, char **av)
{
    t_init init;
    int i = 0;
    pthread_t philo[ft_atoi(av[1])];
    t_philos philos[ft_atoi(av[1])];
    int ret = 0;
    if(ac < 5 || ac > 6)
        return(1);
    initialyze(&init, av, ac);
    dprintf(1, "qweqweq");
   
    if (!(philos[0].table->fork = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t) * init.n_philo)))
        return(0);
    dprintf(1, "qweqweq");
    if (!(philos[.table->i_fork = (int*)malloc(sizeof(int)* init.n_philo)))
        return(0);
    dprintf(1, "qweqweq");
    while(i < init.n_philo)
    {
        init_philo(&philos[i], init, i + 1);
        i++;
    }
    i = 0;
    while(i < init.n_philo)
    {
        if (i == 0)
        {
            philos[i].table->next_fork = philos[i + 1].table->fork;
            if (!(philos[i].table->talk = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t) * 1)))
                return(0);
            philos[i].table->stop = 0;
        }
        else if(i == init.n_philo - 1)
        {
            philos[i].table->next_fork = philos[0].table->fork;
            philos[i].table->stop = philos[0].table->stop;
            philos[i].table->talk = philos[0].table->talk;
        }
        else
        {
            philos[i].table->next_fork = philos[i + 1].table->fork;
            philos[i].table->stop = philos[0].table->stop;
            philos[i].table->talk = philos[0].table->talk;
        }
        i++;
    }
    i = 0;
    while(i < init.n_philo)
    {
        pthread_create(&philo[i], NULL, routine, (void *)&philos[i]);
        i++;
    }
    i = 0;
    printf("Before Thread\n");
    while(i < init.n_philo)
    {
        pthread_join(philo[i], NULL);
        // dprintf(1,"[%d] = %d\n",i +1, ret);
        i++;
    }
    printf("After Thread\n");
    return 0;
}
