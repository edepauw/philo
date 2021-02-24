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

typedef struct  s_philos
{
    t_init init;
    int id;
    long last_eat;
    int *stop;
    pthread_mutex_t *fork;
    pthread_mutex_t *talk;
    pthread_mutex_t *next_fork;
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
    while (1)
    {
        usleep(10);
        philos->last_eat = start.tv_usec;
        if(philos->stop)
            return NULL;
        pthread_mutex_lock (philos->next_fork);
        status(philos->id, "has taken a fork", philos->talk);
        pthread_mutex_lock (philos->fork);
        status(philos->id, "has taken a fork", philos->talk);
        gettimeofday(&start, NULL);
        if(start.tv_usec  - philos->last_eat  > philos->init.t_die *1000)
        {
            status(philos->id, "died", philos->talk);
            *philos->stop = 1;
            return NULL;//die
        }
        if(philos->stop)
            return NULL;
        status(philos->id, "is eating", philos->talk);
        usleep(philos->init.t_eat * 1000);
        if(philos->stop)
            return NULL;
        pthread_mutex_unlock (philos->fork);
        pthread_mutex_unlock (philos->next_fork);
        status(philos->id, "release fork", philos->talk);
        if(philos->stop)
            return NULL;
        status(philos->id, "is sleeping", philos->talk);
        usleep(philos->init.t_sleep * 1000);
        status(philos->id, "is thinking", philos->talk);
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
    if (!(philos->fork = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t) * 1)))
        return(0);
    pthread_mutex_init(philos->fork, NULL);
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
    printf("Before Thread\n");
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
            philos[i].next_fork = philos[i + 1].fork;
            if (!(philos[i].stop = (int*)malloc(sizeof(int))))
                return(0);
            if (!(philos[i].talk = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t) * 1)))
                return(0);
            philos[i].stop = 0;
        }
        else if(i == init.n_philo - 1)
        {
            philos[i].next_fork = philos[0].fork;
            philos[i].stop = philos[0].stop;
            philos[i].talk = philos[0].talk;
        }
        else
        {
            philos[i].next_fork = philos[i + 1].fork;
            philos[i].stop = philos[0].stop;
            philos[i].talk = philos[0].talk;
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
