/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: analexan <analexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 19:09:58 by andrealex         #+#    #+#             */
/*   Updated: 2024/02/15 15:31:34 by analexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL))
		return (0);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	finished(void)
{
	return (get_int(&tb()->finished_mtx, &tb()->finished));
}

static void	check_full(void)
{
	int	i;

	i = 0;
	// pthread_mutex_lock(&tb()->tb_mtx);
	while (tb()->meals_needed != -1 && i < tb()->n_of_philo
		&& tb()->philos[i].meals_eaten >= tb()->meals_needed)
		i++;
	// pthread_mutex_unlock(&tb()->tb_mtx);
	pthread_mutex_lock(&tb()->finished_mtx);
	if (i >= tb()->n_of_philo)
		tb()->finished = 0;
	pthread_mutex_unlock(&tb()->finished_mtx);
}

static void	check_death(void)
{
	int		i;
	size_t	time;

	i = -1;
	while (++i < tb()->n_of_philo && finished())
	{
		time = get_time();
		if ((time - tb()->philos[i].last_meal_time) >= tb()->time_to_die)
		{
			print_message("died", &tb()->philos[i]);
			set_int(&tb()->finished_mtx, &tb()->finished, 0);
		}
	}
}

void	monitor(void)
{
	while (finished())
	{
		check_full();
		if (!finished())
			break ;
		check_death();
	}
}
