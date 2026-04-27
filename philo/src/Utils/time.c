/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalfonso <nalfonso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 22:11:38 by nalfonso          #+#    #+#             */
/*   Updated: 2026/04/27 22:45:06 by nalfonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philosophers.h"

long	get_time_ms(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) != 0)
		return (-1);
	return ((long)tv.tv_sec * 1000L + (long)tv.tv_usec / 1000L);
	
}

int	ft_usleep(long ms, t_data *data)
{
	long	start;
	int		stopped;

	start = get_time_ms();
	while((get_time_ms() - start) < ms)
	{
		pthread_mutex_lock(data->stop_mutex);
		stopped = data->stop;
		pthread_mutex_unlock(data->stop_mutex);
		if (stopped)
			return (-1);
		usleep(500);
	}
	return (0);
}
