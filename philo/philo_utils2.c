/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: analexan <analexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 19:10:05 by andrealex         #+#    #+#             */
/*   Updated: 2024/02/15 15:26:13 by analexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_usleep(size_t time)
{
	size_t	st;

	st = get_time();
	while ((get_time() - st) < time && finished())
		usleep(10);
}

void	print_message(char *str, t_philo *philo)
{
	size_t	time;

	if (!finished())
		return ;
	pthread_mutex_lock(&tb()->print_mtx);
	time = get_time();
	printf("%zu %d %s\n", time - tb()->start_time, philo->id, str);
	pthread_mutex_unlock(&tb()->print_mtx);
}

// mtx is the mutex you want to lock, dest is the int you want to get
int	get_int(pthread_mutex_t *mtx, int *dest)
{
	int	ret;

	pthread_mutex_lock(mtx);
	ret = *dest;
	pthread_mutex_unlock(mtx);
	return (ret);
}

// mtx is the mutex you want to lock, dest is the int you want to set
// value is the value you want to set dest to
void	set_int(pthread_mutex_t *mtx, int *dest, int value)
{
	pthread_mutex_lock(mtx);
	*dest = value;
	pthread_mutex_unlock(mtx);
}

void	clean_table(void)
{
	int	i;

	i = -1;
	while (++i < tb()->n_of_philo)
		if (pthread_join(tb()->philos[i].thread, 0))
			printf("error: pthread_join\n");
	i = -1;
	while (++i < tb()->n_of_philo)
		pthread_mutex_destroy(&tb()->forks[i]);
	pthread_mutex_destroy(&tb()->print_mtx);
	pthread_mutex_destroy(&tb()->finished_mtx);
	free(tb()->forks);
	free(tb()->philos);
}
