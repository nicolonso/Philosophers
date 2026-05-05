/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalfonso <nalfonso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 22:22:01 by nalfonso          #+#    #+#             */
/*   Updated: 2026/05/05 22:26:39 by nalfonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	log_state(t_philo *p, char *state)
{
	long	ts;

	pthread_mutex_lock(&p->data->print_mutex);
	pthread_mutex_lock(&p->data->stop_mutex);
	if (p->data->stop)
	{
		pthread_mutex_unlock(&p->data->stop_mutex);
		pthread_mutex_unlock(&p->data->print_mutex);
		return ;
	}
	pthread_mutex_unlock(&p->data->stop_mutex);
	ts = get_time_ms() - p->data->start_time;
	printf("%ld %d %s\n", ts, p->id, state);
	pthread_mutex_unlock(&p->data->print_mutex);
}
