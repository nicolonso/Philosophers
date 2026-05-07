/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalfonso <nalfonso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 21:53:30 by nalfonso          #+#    #+#             */
/*   Updated: 2026/05/07 21:49:26 by nalfonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

/* ── libraries ──────────────────────────────────────── */
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h> 
# include <semaphore.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>

/* ── named semaphores ─ leading slash REQUIRED ────────── */

# define SEM_FORKS "/philo_forks"
# define SEM_PRINT "/philo_print"
# define SEM_DEATH "/philo_death"

/* ── structs ──────────────────────────────────────── */

typedef struct s_data	t_data;

typedef struct s_philosophers
{
	int				id;
	long			meals_eaten;
	long			last_meal;
	t_data			*data;	
	pthread_t		death_watcher;
	pthread_mutex_t	meal_mutex;
}					t_philo;

typedef struct s_data
{
	int				nb_philo;
	long			must_eat;
	long			start_time;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	pid_t			*pids;
	sem_t			*forks;
	sem_t			*print;
	sem_t			*death;
}					t_data;

/* ── parsing ──────────────────────────────────────── */

long	ft_itoal(char *str);
int		check_digits(char *s, int counter);
int		parse(int ac, char **av, t_data *data);

/* ── time helpers ──────────────────────────────────────── */

long	get_time_ms(void);
void	ft_usleep(long ms);

/* ── init / cleanup ──────────────────────────────────────── */

int		init_data(t_data *data);
void	cleanup(t_data *data);

#endif
