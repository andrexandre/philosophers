/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: analexan <analexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 19:09:53 by andrealex         #+#    #+#             */
/*   Updated: 2024/02/15 15:30:41 by analexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&tb()->forks[philo->first_fork]);
	print_message("has taken a fork", philo);
	pthread_mutex_lock(&tb()->forks[philo->second_fork]);
	print_message("has taken a fork", philo);
	print_message("is eating", philo);
	ft_usleep(tb()->time_to_eat);
	// pthread_mutex_lock(&tb()->tb_mtx);
	philo->last_meal_time = get_time();
	philo->meals_eaten++;
	// pthread_mutex_unlock(&tb()->tb_mtx);
	pthread_mutex_unlock(&tb()->forks[philo->second_fork]);
	pthread_mutex_unlock(&tb()->forks[philo->first_fork]);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (tb()->n_of_philo == 1)
	{
		print_message("has taken a fork", philo);
		ft_usleep(tb()->time_to_die);
	}
	while (finished())
	{
		if (philo->id % 2)
			usleep(100);
		if (tb()->meals_needed != -1
			&& philo->meals_eaten >= tb()->meals_needed)
			break ;
		eat(philo);
		print_message("is sleeping", philo);
		ft_usleep(tb()->time_to_sleep);
		print_message("is thinking", philo);
	}
	return (NULL);
}

int	init_table(void)
{
	int	i;

	tb()->finished = 1;
	pthread_mutex_init(&tb()->print_mtx, NULL);
	pthread_mutex_init(&tb()->finished_mtx, NULL);
	i = -1;
	while (++i < tb()->n_of_philo)
		pthread_mutex_init(&tb()->forks[i], NULL);
	i = -1;
	tb()->start_time = get_time();
	while (++i < tb()->n_of_philo)
	{
		tb()->philos[i].id = i + 1;
		tb()->philos[i].last_meal_time = get_time();
		tb()->philos[i].first_fork = i;
		tb()->philos[i].second_fork = (i + 1) % tb()->n_of_philo;
		if (i % 2 == 0)
			tb()->philos[i].first_fork = (i + 1) % tb()->n_of_philo;
		if (i % 2 == 0)
			tb()->philos[i].second_fork = i;
		if (pthread_create(&tb()->philos[i].thread, NULL, &routine,
				&tb()->philos[i]))
			return (printf("error: pthread create"), 1);
	}
	return (0);
}

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

int	main(int argc, char **argv)
{
	if (error(argc, argv))
		return (-1);
	if (!tb()->meals_needed)
		return (0);
	(tb()->forks) = ft_calloc(tb()->n_of_philo, sizeof(pthread_mutex_t));
	if (!tb()->forks)
		return (printf("error: malloc\n"), 1);
	(tb()->philos) = ft_calloc(tb()->n_of_philo, sizeof(t_philo));
	if (!tb()->philos)
		return (free(tb()->forks), printf("error: malloc\n"), 1);
	if (init_table())
		return (-1);
	monitor();
	clean_table();
	return (0);
}
