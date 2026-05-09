/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalfonso <nalfonso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 21:58:16 by nalfonso          #+#    #+#             */
/*   Updated: 2026/05/09 16:34:27 by nalfonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int fork_children(t_data *data)
{
	int		i;
	pid_t	pid;

	i = 0;
	while (i < data->nb_philo)
	{
		pid = fork();
		if (pid < 0)
		{
			while (--i >= 0)
				kill(data->pids[i], SIGKILL);
			while (++i <= 0)
				;
			while (i < data->nb_philo)
			{
				waitpid(data->pids[i], NULL, 0);
				i++;
			}
			return (1);
		}
		if (pid == 0)
		{
			child_run(i, data);
			exit (1);
		}
		data->pids[i] = pid;
		i++;
	}
	return (0);
}

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
