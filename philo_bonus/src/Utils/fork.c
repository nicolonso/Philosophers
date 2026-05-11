/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalfonso <nalfonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 18:08:50 by nalfonso          #+#    #+#             */
/*   Updated: 2026/05/11 18:42:48 by nalfonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	helper(t_data *data, int *i)
{
	while (--(*i) >= 0)
		kill(data->pids[*i], SIGKILL);
	while (++(*i) <= 0)
		;
	while (*i < data->nb_philo)
	{
		waitpid(data->pids[*i], NULL, 0);
		(*i)++;
	}
}

int	fork_children(t_data *data)
{
	int		i;
	pid_t	pid;

	i = 0;
	while (i < data->nb_philo)
	{
		pid = fork();
		if (pid < 0)
		{
			helper(data, &i);
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
