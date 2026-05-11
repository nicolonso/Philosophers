/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalfonso <nalfonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 22:11:38 by nalfonso          #+#    #+#             */
/*   Updated: 2026/05/11 18:24:25 by nalfonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	get_time_ms(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) != 0)
		return (-1);
	return ((long)tv.tv_sec * 1000L + (long)tv.tv_usec / 1000L);
}

void	ft_usleep(long ms)
{
	long	start;

	start = get_time_ms();
	while ((get_time_ms() - start) < ms)
		usleep(500);
}
