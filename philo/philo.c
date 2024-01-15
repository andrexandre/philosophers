#include "philo.h"

int	error(int ac, char **av)
{
	int		i;
	int		j;
	char 	*err_msg;

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
				return (printf("syntax: non digit sent\n"), 1);
	}
	ph()->n_of_philosophers = ft_atoi(av[1]);
	ph()->time_to_die = ft_atoi(av[2]);
	ph()->time_to_eat = ft_atoi(av[3]);
	ph()->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		ph()->meals_needed = ft_atoi(av[5]);
	else
		ph()->meals_needed = -1;
	return (0);
}

// to-do: finish parsing (if O < i < 60 quit)
int	main(int ac, char **av)
{
	// (void)ac;
	// (void)av;
	if (error(ac, av))
		return (1);
	else
		printf("nf: %d\nttd: %d\ntte: %d\ntts: %d\nmn: %d\n",
			ph()->n_of_philosophers, ph()->time_to_die, ph()->time_to_eat,
			ph()->time_to_sleep, ph()->meals_needed);
	return (0);
}
