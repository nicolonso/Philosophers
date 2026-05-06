/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalfonso <nalfonso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 22:22:42 by nalfonso          #+#    #+#             */
/*   Updated: 2026/05/06 22:52:45 by nalfonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	stopped(t_data *data)
{
	int	v;

	pthread_mutex_lock(&data->stop_mutex);
	v = data->stop;
	pthread_mutex_unlock(&data->stop_mutex);
	return (v);
}

static void	take_forks(t_philo *p)
{
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;

	if (p->left_fork < p->right_fork)
	{
		first = p->left_fork;
		second = p->right_fork;
	}
	else
	{
		first = p->right_fork;
		second = p->left_fork;
	}
	pthread_mutex_lock(first);
	log_state(p, "has taken a fork");
	pthread_mutex_lock(second);
	log_state(p, "has taken a fork");
}

static void	eat(t_philo *p)
{
	pthread_mutex_lock(&p->data->meal_mutex);
	p->last_meal = get_time_ms();
	p->meals_eaten++;
	pthread_mutex_unlock(&p->data->meal_mutex);
	log_state(p, "is eating");
	ft_usleep(p->data->time_to_eat, p->data);
}

void	*routine(void *arg)
{
	t_philo	*p;

	p = (t_philo *)arg;
	if (p->data->nb_philo == 1)
	{
		log_state(p, "has taken a fork");
		ft_usleep(p->data->time_to_die + 10, p->data);
		return (NULL);
	}
	if (p->id % 2 == 0)
		ft_usleep(p->data->time_to_eat / 2, p->data);
	while (!stopped(p->data))
	{
		log_state(p, "is thinking");
		take_forks(p);
		eat(p);
		pthread_mutex_unlock(p->left_fork);
		pthread_mutex_unlock(p->right_fork);
		log_state(p, "is sleeping");
		ft_usleep(p->data->time_to_sleep, p->data);
	}
	return (NULL);
}
