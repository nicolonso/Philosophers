/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalfonso <nalfonso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 21:53:30 by nalfonso          #+#    #+#             */
/*   Updated: 2026/05/09 16:55:36 by nalfonso         ###   ########.fr       */
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
# define SEM_DONE "/philo_done"
# define SEM_EATERS	"/philo_eaters"

/* ── structs ──────────────────────────────────────── */

typedef struct s_data	t_data;

typedef struct s_philosophers
{
	int				id;
	int				done;
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
	sem_t			*done;
	sem_t			*eaters;
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

/* ── log ──────────────────────────────────────────────── */

void	log_print(t_philo *p, char *state);

/* ── child / supervisor ───────────────────────────────── */

void	child_run(int id, t_data *data);
int		supervise(t_data *data);

#endif
