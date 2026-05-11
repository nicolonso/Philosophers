/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalfonso <nalfonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 21:15:32 by nalfonso          #+#    #+#             */
/*   Updated: 2026/05/11 18:22:33 by nalfonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	unlink_all_sems(void)
{
	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_PRINT);
	sem_unlink(SEM_DEATH);
	sem_unlink(SEM_DONE);
	sem_unlink(SEM_EATERS);
}

static int	open_all_sems(t_data *data)
{
	int	eat;

	data->forks = sem_open(SEM_FORKS, O_CREAT | O_EXCL, 0644,
			data->nb_philo);
	if (data->forks == SEM_FAILED)
		return (1);
	data->print = sem_open(SEM_PRINT, O_CREAT | O_EXCL, 0644, 1);
	if (data->print == SEM_FAILED)
		return (1);
	data->death = sem_open(SEM_DEATH, O_CREAT | O_EXCL, 0644, 0);
	if (data->death == SEM_FAILED)
		return (1);
	data->done = sem_open(SEM_DONE, O_CREAT | O_EXCL, 0644, 0);
	if (data->done == SEM_FAILED)
		return (1);
	eat = data->nb_philo / 2;
	if (eat <= 0)
		eat = 1;
	data->eaters = sem_open(SEM_EATERS, O_CREAT | O_EXCL, 0644, eat);
	if (data->eaters == SEM_FAILED)
		return (1);
	return (0);
}

int	init_data(t_data *data)
{
	data->start_time = get_time_ms();
	data->forks = SEM_FAILED;
	data->print = SEM_FAILED;
	data->death = SEM_FAILED;
	data->done = SEM_FAILED;
	data->eaters = SEM_FAILED;
	data->pids = NULL;
	unlink_all_sems();
	if (open_all_sems(data))
	{
		cleanup(data);
		return (1);
	}
	data->pids = malloc(sizeof(pid_t) * data->nb_philo);
	if (!data->pids)
	{
		cleanup(data);
		return (1);
	}
	return (0);
}
