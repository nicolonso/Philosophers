/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalfonso <nalfonso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 21:58:16 by nalfonso          #+#    #+#             */
/*   Updated: 2026/04/29 22:21:07 by nalfonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int ac, char **av)
{
	t_data 	data;
	// long	t1;
	// long	t2;

	if (parse(ac, av, &data))
	{
		write (2, "Parametrers are incorrect\n", 27);
		return (1);
	}
	/* t1 = get_time_ms();
	usleep(1000000);
	t2 = get_time_ms();
	printf("elapsed: %ld ms (expect ~100)\n", t2 - t1); */
	if (init_data(&data))
	{
		write (2, "Init failed\n", 12);
		return (1);
	}
	cleanup(&data);
	return (0);
}
