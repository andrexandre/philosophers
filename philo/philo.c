#include "philo.h"

int	error(int ac, char **av)
{
	int		i;
	int		j;

	if (ac < 5 || ac > 6)
		return (printf("syntax: ./philo number_of_philo time_to_die \
time_to_eat time_to_sleep [meals_needed]\n"), 1);
	i = 0;
	while (++i < ac)
	{
		j = -1;
		while (av[i][++j])
			if (!ft_isdigit(av[i][j]) || j > 8)
				return (printf("syntax: non digit/negative number sent or \
number too big\n"), 1);
	}
	tb()->n_of_philo = ft_atoi(av[1]);
	tb()->time_to_die = ft_atoi(av[2]);
	tb()->time_to_eat = ft_atoi(av[3]);
	tb()->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		tb()->meals_needed = ft_atoi(av[5]);
	else
		tb()->meals_needed = -1;
	return (0);
}

int	init_table(void)
{
	int	i;

	(tb()->forks) = ft_calloc(tb()->n_of_philo, sizeof(t_fork));
	if (!tb()->forks)
		return (printf("error: malloc\n"), 1);
	(tb()->philos) = ft_calloc(tb()->n_of_philo, sizeof(t_philo));
	if (!tb()->philos)
		return (printf("error: malloc\n"), 1);
	i = -1;
	pthread_mutex_init(&tb()->tb_mtx, NULL);
	pthread_mutex_init(&tb()->print, NULL);
	while (++i < tb()->n_of_philo)
	{
		tb()->philos[i].first_fork = &tb()->forks[(i + 1) % tb()->n_of_philo];
		tb()->philos[i].second_fork = &tb()->forks[i];
		if (i % 2 == 0)
			tb()->philos[i].first_fork = &tb()->forks[i];
		if (i % 2 == 0)
			tb()->philos[i].second_fork = &tb()->forks[(i + 1) % tb()->n_of_philo];
		pthread_mutex_init(&tb()->forks[i].mtx, NULL);
		pthread_mutex_init(&tb()->philos[i].ph_mtx, NULL);
		tb()->forks[i].id = i;
		tb()->philos[i].id = i;
	}
	return (0);
}

void	clean_table(void)
{
	int	i;

	i = -1;
	while (++i < tb()->n_of_philo)
	{
		pthread_mutex_destroy(&tb()->forks[i].mtx);
		pthread_mutex_destroy(&tb()->philos[i].ph_mtx);
	}
	pthread_mutex_destroy(&tb()->tb_mtx);
	pthread_mutex_destroy(&tb()->print);
	free(tb()->forks);
	free(tb()->philos);
}

void	wait_all_threads(void)
{
	while (!get_int(&tb()->tb_mtx, &tb()->all_threads_ready))
		;
}

void	ft_usleep(int time)
{
	long	start;

	start = get_time();
	while (get_time() - start < time)
	{
		if (philo_finished())
			break ;
		usleep(100);
	}
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->first_fork->mtx);
	print_action(philo, A_FFORK);
	pthread_mutex_lock(&philo->second_fork->mtx);
	print_action(philo, A_SFORK);
	set_int(&philo->ph_mtx, &philo->last_meal_time, get_time());
	philo->meals_eaten++;
	print_action(philo, A_EAT);
	ft_usleep(tb()->time_to_eat * 1000);
	if (tb()->meals_needed != -1 && philo->meals_eaten == tb()->meals_needed)
		set_int(&philo->ph_mtx, &philo->full, 1);
	pthread_mutex_unlock(&philo->first_fork->mtx);
	pthread_mutex_unlock(&philo->second_fork->mtx);
}

// increate the threads running to sync with the monitor
void	increase_int(t_mtx *mtx, int *dest)
{
	pthread_mutex_lock(mtx);
	(*dest)++;
	pthread_mutex_unlock(mtx);
}

void	*routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_all_threads();

	set_int(&philo->ph_mtx, &philo->last_meal_time, get_time());

	increase_int(&tb()->tb_mtx, &tb()->threads_running_num);
	while (!philo_finished())
	{
		if (philo->full)
			break ;
		eat(philo);
		print_action(philo, A_SLEEP);
		ft_usleep(tb()->time_to_sleep * 1000);
		print_action(philo, A_THINK);
	}
	return (NULL);
}

int	all_thread_running(void)
{
	int	ret;

	ret = 0;
	pthread_mutex_lock(&tb()->tb_mtx);
	if (tb()->threads_running_num == tb()->n_of_philo)
		ret = 1;
	pthread_mutex_unlock(&tb()->tb_mtx);
	return (ret);
}

int	philo_died(t_philo *philo)
{
	int elapsed;

	if (get_int(&philo->ph_mtx, &philo->full))
		return (0);
	elapsed = get_time() - get_int(&philo->ph_mtx, &philo->last_meal_time);
	if (elapsed > tb()->time_to_die)
	{
		printf("philo %d died\n", philo->id);
		return (1);
	}
	return (0);
}

void	*monitor(void *data)
{
	int	i;
	(void)data;
	while (!all_thread_running())
		;
	while (!philo_finished())
	{
		i = -1;
		while (++i < tb()->n_of_philo)
		{
			if (philo_died(&tb()->philos[i]))
			{
				set_int(&tb()->tb_mtx, &tb()->finished, 1);
				print_action(&tb()->philos[i], A_DIE);
			}
		}
	}
	return (NULL);
}

void	*lone_philo(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_all_threads();
	set_int(&philo->ph_mtx, &philo->last_meal_time, get_time());
	increase_int(&tb()->tb_mtx, &tb()->threads_running_num);
	print_action(philo, A_SLEEP);
	while (!philo_finished())
		ft_usleep(200);
	return (NULL);
}

void	dinner_start(void)
{
	int	i;

	i = -1;
	if (tb()->n_of_philo == 1)
	{
		if (pthread_create(&tb()->philos[0].thread, NULL, lone_philo, &tb()->philos[i]))
			printf("error: pthread create\n");
	}
	else
	{
		while (++i < tb()->n_of_philo)
		{
			if (pthread_create(&tb()->philos[i].thread, NULL, routine, &tb()->philos[i]))
				printf("error: pthread create\n");
		}
	}
	pthread_create(&tb()->monitor, NULL, monitor, NULL);
	tb()->start_time = get_time();
	set_int(&tb()->tb_mtx, &tb()->all_threads_ready, 1);
	i = -1;
	while (++i < tb()->n_of_philo)
		if (pthread_join(tb()->philos[i].thread, NULL))
			printf("error: pthread join\n");
	set_int(&tb()->tb_mtx, &tb()->finished, 1);
	pthread_join(tb()->monitor, NULL);
}

int	main(int ac, char **av)
{
	if (error(ac, av))
		return (1);
printf("./philo number_of_philo time_to_die \
time_to_eat time_to_sleep [meals_needed]\n");
	if (tb()->meals_needed == 0)
		return (0);
	if (init_table())
		return (1);
	dinner_start();
	clean_table();
	return (0);
}

/*
./philo 5 280 200 202020 7
program should end when a philo dies
*/