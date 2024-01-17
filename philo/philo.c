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

void	*routine(void *data)
{
	(void)data;
	tb()->start_time = get_time();
	return (NULL);
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
	while (++i < tb()->n_of_philo)
	{
		tb()->philos[i].right_fork = &tb()->forks[i];
		tb()->philos[i].left_fork = &tb()->forks[(i + 1) % tb()->n_of_philo];
		if (pthread_mutex_init(&tb()->forks[i].mtx, NULL))
			return (printf("error: mutex init\n"), 1);
		tb()->forks[i].id = i;
	}
	i = -1;
	while (++i < tb()->n_of_philo)
	{
		tb()->philos[i].id = i;
		if (pthread_create(&tb()->philos[i].thread, NULL, &routine, \
		&tb()->philos[i]))
			return (printf("error: thread creation\n"), 1);
	}
	return (0);
}

void	clean_table(void)
{
	int	i;

	i = -1;
	while (++i < tb()->n_of_philo)
		pthread_join(tb()->philos[i].thread, NULL);
	i = -1;
	while (++i < tb()->n_of_philo)
		pthread_mutex_destroy(&tb()->forks[i].mtx);
	free(tb()->forks);
	free(tb()->philos);
}

int	main(int ac, char **av)
{
	if (error(ac, av))
		return (1);
	if (tb()->meals_needed == 0)
		return (0);
	// if (tb()->n_of_philo == 1)
	// 	special_function();
	if (init_table())
		return (1);
	printf("nf: %d, ttd: %d, tte: %d, tts: %d, mn: %d\n", tb()->n_of_philo, \
	tb()->time_to_die, tb()->time_to_eat, tb()->time_to_sleep, \
	tb()->meals_needed);
	clean_table();
	return (0);
}
