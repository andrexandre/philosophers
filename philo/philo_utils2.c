#include "philo.h"

long	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (-1);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	print_action(t_philo *philo, enum e_action action)
{
	int		elapsed;

	elapsed = get_time() - tb()->start_time;
	if (philo->full)
		return ;
	if (philo_finished())
		return ;
	pthread_mutex_lock(&tb()->print);
	if (action == A_FFORK || action == A_SFORK)
		printf(WHITE "%d %d has taken a fork" , elapsed, philo->id);
	else if (action == A_EAT)
		printf(YELLOW "%d %d is eating\n" RESET, elapsed, philo->id);
	else if (action == A_SLEEP)
		printf(BLUE "%d %d is sleeping\n" RESET, elapsed, philo->id);
	else if (action == A_THINK)
		printf(GREEN "%d %d is thinking\n" RESET, elapsed, philo->id);
	else if (action == A_DIE)
		printf(RED "%d %d died\n" RESET, elapsed, philo->id);
	if (action == A_FFORK)
		printf(" 1st fork [ %d ]\n"RESET, philo->first_fork->id);
	else if (action == A_SFORK)
		printf(" 2nd fork [ %d ]\n"RESET, philo->second_fork->id);
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

int	philo_finished(void)
{
	return (get_int(&tb()->tb_mtx, &tb()->finished));
}
