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

# define RESET		"\033[0m"
# define BLACK		"\033[30m"
# define WHITE		"\033[37m"// fork
# define RED		"\033[31m"// death
# define GREEN		"\033[32m"// think
# define YELLOW		"\033[33m"// eat
# define BLUE		"\033[34m"// sleep
# define MAGENTA	"\033[35m"
# define CYAN		"\033[36m"

enum e_action
{
	A_FORK,
	A_EAT,
	A_SLEEP,
	A_THINK,
	A_DIE
};

typedef pthread_mutex_t	t_mtx;

typedef struct s_fork
{
	int				id;
	t_mtx			mtx;
}					t_fork;

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	int				last_meal;
	t_fork			*left_fork;
	t_fork			*right_fork;
	pthread_t		thread;
}					t_philo;

typedef struct s_table
{
	int				n_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meals_needed;
	int				start_time;
	int				finished;
	int				all_threads_ready;
	t_mtx			mtx;
	t_mtx			print;
	t_fork			*forks;
	t_philo			*philos;
}					t_table;

// philo_utils
int		ft_isdigit(int c);
int		ft_atoi(const char *nptr);
void	*ft_calloc(size_t nmemb, size_t size);
t_table	*tb(void);

// philo_utils2
long	get_time(void);
void	print_action(int n_philo, enum e_action action);

#endif