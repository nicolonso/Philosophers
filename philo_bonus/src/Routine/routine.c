/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalfonso <nalfonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 22:22:42 by nalfonso          #+#    #+#             */
/*   Updated: 2026/05/11 18:23:41 by nalfonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	*death_watcher(void *arg)
{
	t_philo	*p;
	long	now;
	long	elapsed;
	int		is_done;

	p = (t_philo *)arg;
	while (1)
	{
		pthread_mutex_lock(&p->meal_mutex);
		now = get_time_ms();
		elapsed = now - p->last_meal;
		is_done = p->done;
		pthread_mutex_unlock(&p->meal_mutex);
		if (!is_done && elapsed > p->data->time_to_die)
		{
			sem_wait(p->data->print);
			printf("%ld %d died\n", now - p->data->start_time, p->id);
			sem_post(p->data->death);
			exit (1);
		}
		usleep(1000);
	}
	return (NULL);
}

static void	take_two_forks(t_philo *p)
{
	sem_wait(p->data->eaters);
	sem_wait(p->data->forks);
	log_print(p, "has taken a fork");
	sem_wait(p->data->forks);
	log_print(p, "has taken a fork");
}

static void	eat_one_meal(t_philo *p)
{
	pthread_mutex_lock(&p->meal_mutex);
	p->last_meal = get_time_ms();
	p->meals_eaten++;
	pthread_mutex_unlock(&p->meal_mutex);
	log_print(p, "is eating");
	ft_usleep(p->data->time_to_eat);
}

static void	mark_done_and_wait(t_philo *p)
{
	pthread_mutex_lock(&p->meal_mutex);
	p->done = 1;
	pthread_mutex_unlock(&p->meal_mutex);
	sem_post(p->data->done);
	while (1)
		usleep(100000);
}

void	child_run(int id, t_data *data)
{
	t_philo	philo;

	philo.id = id + 1;
	philo.meals_eaten = 0;
	philo.last_meal = data->start_time;
	philo.done = 0;
	philo.data = data;
	pthread_mutex_init(&philo.meal_mutex, NULL);
	pthread_create(&philo.death_watcher, NULL, death_watcher, &philo);
	pthread_detach(philo.death_watcher);
	if (philo.id % 2 == 0)
		ft_usleep(data->time_to_eat / 2);
	while (1)
	{
		log_print(&philo, "is thinking");
		take_two_forks(&philo);
		eat_one_meal(&philo);
		sem_post(data->forks);
		sem_post(data->forks);
		sem_post(data->eaters);
		if (data->must_eat != -1 && philo.meals_eaten >= data->must_eat)
			mark_done_and_wait(&philo);
		log_print(&philo, "is sleeping");
		ft_usleep(data->time_to_sleep);
	}
}
