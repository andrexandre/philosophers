/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: analexan <analexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 19:10:18 by andrealex         #+#    #+#             */
/*   Updated: 2024/01/24 17:44:30 by analexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	int				id;
	int				first_fork;
	int				second_fork;
	int				meals_eaten;
	size_t			last_meal_time;
	pthread_t		thread;
}					t_philo;

typedef struct s_table
{
	int				n_of_philo;
	int				meals_needed;
	int				finished;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			start_time;
	pthread_mutex_t	print_mtx;
	pthread_mutex_t	finished_mtx;
	pthread_mutex_t	*forks;
	t_philo			*philos;
}					t_table;

// monitor
size_t				get_time(void);
int					finished(void);
void				monitor(void);

// philo_utils
int					ft_isdigit(int c);
int					ft_atoi(const char *nptr);
void				*ft_calloc(size_t nmemb, size_t size);
t_table				*tb(void);

// philo_utils2
void				ft_usleep(size_t time);
void				print_message(char *str, t_philo *philo);
int					get_int(pthread_mutex_t *mtx, int *dest);
void				set_int(pthread_mutex_t *mtx, int *dest, int value);
void				clean_table(void);

#endif