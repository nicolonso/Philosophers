/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalfonso <nalfonso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 22:22:49 by nalfonso          #+#    #+#             */
/*   Updated: 2026/05/06 22:53:11 by nalfonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	check_one_death(t_philo *p, int *out_id)
{
	long	now;
	int		dead;

	dead = 0;
	now = get_time_ms();
	pthread_mutex_lock(&p->data->meal_mutex);
	if (now - p->last_meal > p->data->time_to_die)
	{
		*out_id = p->id;
		dead = 1;
	}
	pthread_mutex_unlock(&p->data->meal_mutex);
	return (dead);
}

static int	all_fed(t_data *data)
{
	int	i;
	int	fed;

	if (data->must_eat == -1)
		return (0);
	fed = 1;
	pthread_mutex_lock(&data->meal_mutex);
	i = 0;
	while (i < data->nb_philo)
	{
		if (data->philos[i].meals_eaten < data->must_eat)
		{
			fed = 0;
			break ;
		}
		i++;
	}
	pthread_mutex_unlock(&data->meal_mutex);
	return (fed);
}

static void	declare_death(t_data *data, int dead_id)
{
	long	ts;

	pthread_mutex_lock(&data->print_mutex);
	pthread_mutex_lock(&data->stop_mutex);
	data->stop = 1;
	pthread_mutex_unlock(&data->stop_mutex);
	ts = get_time_ms() - data->start_time;
	printf("%ld %d died\n", ts, dead_id);
	pthread_mutex_unlock(&data->print_mutex);
}

static void	set_stop_silent(t_data *data)
{
	pthread_mutex_lock(&data->stop_mutex);
	data->stop = 1;
	pthread_mutex_unlock(&data->stop_mutex);
}

void	*monitor(void *arg)
{
	t_data	*data;
	int		i;
	int		dead_id;

	data = (t_data *)arg;
	while (1)
	{
		i = 0;
		while (i < data->nb_philo)
		{
			if (check_one_death(&data->philos[i], &dead_id))
			{
				declare_death(data, dead_id);
				return (NULL);
			}
			i++;
		}
		if (all_fed(data))
		{
			set_stop_silent(data);
			return (NULL);
		}
		usleep(1000);
	}
}
