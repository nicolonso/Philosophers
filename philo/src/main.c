/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalfonso <nalfonso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 21:58:16 by nalfonso          #+#    #+#             */
/*   Updated: 2026/05/06 19:54:56 by nalfonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/* static int all_philos_fed(t_data *data)
{
	int	i;
	int	fed;

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
} */

static int start_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_create(&data->philos[i].thread, NULL,
				routine, &data->philos[i]) != 0)
		{
			pthread_mutex_lock(&data->stop_mutex);
			data->stop = 1;
			pthread_mutex_unlock(&data->stop_mutex);
			while (--i >= 0)
				pthread_join(data->philos[i].thread, NULL);
			return (1);
		}
		i++;
	}
	return (0);
}

/* static void wait_until_done(t_data *data)
{
	if (data->must_eat == -1)
		ft_usleep(10000, data);
	else
	{
		while (!all_philos_fed(data))
			usleep(1000);
	}
	pthread_mutex_lock(&data->stop_mutex);
	data->stop = 1;
	pthread_mutex_unlock(&data->stop_mutex);
} */

static void join_threads(t_data *data)
{
	int	i;

	i = 0;
	while(i < data->nb_philo)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
}

int	main(int ac, char **av)
{
	t_data		data;
	pthread_t	monitor_th;
	// long	t1;
	// long	t2;

	if (parse(ac, av, &data))
		return (write (2, "Parametrers are incorrect\n", 27), 1);
	/* t1 = get_time_ms();
	usleep(1000000);
	t2 = get_time_ms();
	printf("elapsed: %ld ms (expect ~100)\n", t2 - t1); */
	if (init_data(&data))
		return (write (2, "Init failed\n", 12), 1);
	if (start_threads(&data))
	{
		write (2, "Thread spawn failed\n", 20);
		cleanup(&data);
		return (1);
	}
	if (pthread_create(&monitor_th, NULL, monitor, &data) != 0)
	{
		pthread_mutex_lock(&data.stop_mutex);
		data.stop = 1;
		pthread_mutex_unlock(&data.stop_mutex);
		join_threads(&data);
		cleanup(&data);
		return (1);
	}
	//wait_until_done(&data);
	pthread_join(monitor_th, NULL);
	join_threads(&data);
	cleanup(&data);
	return (0);
}
