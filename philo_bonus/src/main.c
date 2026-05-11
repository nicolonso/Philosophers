/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalfonso <nalfonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 21:58:16 by nalfonso          #+#    #+#             */
/*   Updated: 2026/05/11 18:09:09 by nalfonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int ac, char **av)
{
	t_data		data;

	if (parse(ac, av, &data))
		return (write (2, "Parametrers are incorrect\n", 27), 1);
	if (init_data(&data))
		return (write (2, "Init failed\n", 12), 1);
	if (fork_children(&data))
	{
		write (2, "Fork failed\n", 12);
		cleanup(&data);
		return (1);
	}
	supervise(&data);
	cleanup(&data);
	return (0);
}
