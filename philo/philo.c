#include "philo.h"

int	error(int ac, char **av)
{
	int		i;
	int		j;
	char	*err_msg;

	i = 0;
	err_msg = "syntax: ./philo number_of_philosophers time_to_die \
time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n";
	if (ac < 5 || ac > 6)
		return (printf("%s", err_msg), 1);
	while (++i < ac)
	{
		j = -1;
		while (av[i][++j])
			if (!ft_isdigit(av[i][j]))
				return (printf("syntax: non digit/negative number sent\n"), 1);
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
	tb()->forks = ft_calloc(tb()->n_of_philo, sizeof(t_fork));
	if (!tb()->forks)
		return (printf("error: malloc\n"), 1);
	tb()->philos = ft_calloc(tb()->n_of_philo, sizeof(t_philo));
	if (!tb()->philos)
		return (printf("error: malloc\n"), 1);
	int i = -1;
	while (++i < tb()->n_of_philo)
		tb()->philos[i].id = i; 
	return (0);
}

void	clean_table(void)
{
	// int	i;

	// i = -1;
	// while (++i < tb()->n_of_philo)
	// 	pthread_mutex_destroy(&tb()->forks[i].mtx);
	free(tb()->forks);
	free(tb()->philos);
}

int	main(int ac, char **av)
{
	if (error(ac, av))
		return (1);
	if (init_table())
		return (1);
	clean_table();
	return (0);
}

/*
◦ timestamp_in_ms X has taken a fork
◦ timestamp_in_ms X is eating
◦ timestamp_in_ms X is sleeping
◦ timestamp_in_ms X is thinking
◦ timestamp_in_ms X died
*/