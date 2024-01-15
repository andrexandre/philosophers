#ifndef PHILO_H
# define PHILO_H
// memset
# include <string.h>
// printf
# include <stdio.h>
// malloc, free
# include <stdlib.h>
// write, usleep
# include <unistd.h>
// gettimeofday
# include <sys/time.h>
// pthread_create, pthread_detach, pthread_join, pthread_mutex_init,
// pthread_mutex_destroy, pthread_mutex_lock, pthread_mutex_unlock
# include <pthread.h>

typedef struct s_philo
{
	int				n_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meals_needed;
	pthread_t		thread;
}				t_philo;

int	ft_isdigit(int c);
int	ft_atoi(const char *nptr);
t_philo	*ph(void);

#endif