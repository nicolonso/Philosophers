/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervisor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalfonso <nalfonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 22:22:49 by nalfonso          #+#    #+#             */
/*   Updated: 2026/05/11 18:22:51 by nalfonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	*done_counter(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	i = 0;
	while (i < data->nb_philo)
	{
		sem_wait(data->done);
		i++;
	}
	sem_post(data->death);
	return (NULL);
}

static void	kill_all(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		kill(data->pids[i], SIGKILL);
		i++;
	}
}

static void	wait_all_children(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		waitpid(data->pids[i], NULL, 0);
		i++;
	}
}

static void	wake_done_counter(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		sem_post(data->done);
		i++;
	}
}

int	supervise(t_data *data)
{
	pthread_t	counter;
	int			has_counter;

	has_counter = 0;
	if (data->must_eat != -1)
	{
		if (pthread_create(&counter, NULL, done_counter, data) == 0)
			has_counter = 1;
	}
	sem_wait(data->death);
	kill_all(data);
	wait_all_children(data);
	if (has_counter)
	{
		wake_done_counter(data);
		pthread_join(counter, NULL);
	}
	return (0);
}
