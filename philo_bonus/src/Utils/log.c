/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalfonso <nalfonso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 22:22:01 by nalfonso          #+#    #+#             */
/*   Updated: 2026/05/09 15:16:12 by nalfonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	log_print(t_philo *p, char *state)
{
	long	ts;

	sem_wait(p->data->print);
	ts = get_time_ms() - p->data->start_time;
	printf("%ld %d %s\n", ts, p->id, state);
	sem_post(p->data->print);
}
