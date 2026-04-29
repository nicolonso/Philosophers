/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalfonso <nalfonso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 21:53:30 by nalfonso          #+#    #+#             */
/*   Updated: 2026/04/29 21:31:23 by nalfonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H

/* ── libraries ──────────────────────────────────────── */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h> // Learn about this library
#include <sys/time.h> // Standard C library (libc, -lc)

/* ── structs ──────────────────────────────────────── */

typedef struct s_data	t_data;

typedef struct s_philosophers
{
	int				id;
	int				meals_eaten;
	long			last_meal;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_data			*data;	
}					t_philo;

typedef struct s_data
{
	int				nb_philo;
	long			must_eat;
	int				stop;
	long			start_time;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	stop_mutex;
	pthread_mutex_t	meal_mutex;
}					t_data;


/* ── parsing ──────────────────────────────────────── */

long	ft_itoal(char *str);
int 	check_digits(char *s, int counter);
int		parse(int ac, char **av , t_data *data);

/* ── time helpers ──────────────────────────────────────── */

long	get_time_ms(void);
int		ft_usleep(long ms, t_data *data);

/* ── init / cleanup ──────────────────────────────────────── */

int		init_data(t_data *data);
void	cleanup(t_data *data);

#endif
