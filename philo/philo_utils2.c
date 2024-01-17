#include "philo.h"

long	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (-1);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	print_action(int n_philo, enum e_action action)
{
	int		elapsed;

	elapsed = get_time() - tb()->start_time;
	pthread_mutex_lock(&tb()->print);
	if (action == A_FORK)
		printf(WHITE "%d %d has taken a fork\n" RESET, elapsed, n_philo);
	else if (action == A_EAT)
		printf(YELLOW "%d %d is eating\n" RESET, elapsed, n_philo);
	else if (action == A_SLEEP)
		printf(BLUE "%d %d is sleeping\n" RESET, elapsed, n_philo);
	else if (action == A_THINK)
		printf(GREEN "%d %d is thinking\n" RESET, elapsed, n_philo);
	else if (action == A_DIE)
		printf(RED "%d %d died\n" RESET, elapsed, n_philo);
	pthread_mutex_unlock(&tb()->print);
}

// mtx is the mutex you want to lock, dest is the int you want to get
int	get_int(t_mtx *mtx, int *dest)
{
	int	ret;

	pthread_mutex_lock(mtx);
	ret = *dest;
	pthread_mutex_unlock(mtx);
	return (ret);
}

// mtx is the mutex you want to lock, dest is the int you want to set
// value is the value you want to set dest to
void	set_int(t_mtx *mtx, int *dest, int value)
{
	pthread_mutex_lock(mtx);
	*dest = value;
	pthread_mutex_unlock(mtx);
}

int	philo_finished(t_table *table)
{
	return (get_int(&table->mtx, &table->finished));
}
