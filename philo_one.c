#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h>  //Header file for sleep(). man 3 sleep for details. 
#include <pthread.h> 
#include "libft/libft.h"
// A normal C function that is executed as a thread  
// when its name is specified in pthread_create() 
typedef struct  s_init
{
    int n_philo;
    int t_eat;
    int t_die;
    int num_philo;
    int t_sleep;
    int n_eat;
}               t_init;

typedef struct  s_philos
{
    int n_philo;
    int t_eat;
    int t_die;
    int num_philo;
    int t_sleep;
    int n_eat
}               t_philos;


void *myThreadFun(void *p_data)
{ 
    t_init *init;

    init = p_data;
    dprintf(1, "salut %d\n", init->num_philo);
    sleep(1);
    dprintf(1, "demitour\n");
    return NULL; 
}
   
void initialyze(t_init *init, char **av, int ac)
{
    init->n_philo = ft_atoi(av[1]);
    init->t_eat = ft_atoi(av[2]);
    init->t_sleep = ft_atoi(av[3]);
    init->t_die = ft_atoi(av[4]);
    if (ac == 6)
        init->n_eat = ft_atoi(av[5]);
}
int main(int ac, char **av) 
{
    t_init init;
    int i = 0;
    pthread_t philo[ft_atoi(av[1])];
    // t_philo philo[ft_atoi(av[1])]
    if(ac != 5)
        return(1);
    initialyze(&init, av, ac);
    printf("Before Thread\n"); 
    while(i < init.n_philo)
    {
        init.num_philo = i + 1;
        pthread_create(&philo[i], NULL, myThreadFun, (void *)&init);
        i++;
    }
    i = 0;
    while(i < init.n_philo)
    {
        pthread_join(philo[i], NULL);
        i++;
    }
    printf("After Thread\n"); 
    exit(0); 
}