/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalfonso <nalfonso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 22:22:35 by nalfonso          #+#    #+#             */
/*   Updated: 2026/05/09 16:57:47 by nalfonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	cleanup(t_data *data)
{
	if (data->forks != SEM_FAILED)
		sem_close(data->forks);
	if (data->print !=  SEM_FAILED)
		sem_close(data->print);
	if (data->death != SEM_FAILED)
		sem_close(data->death);
	if (data->done != SEM_FAILED)
		sem_close(data->done);
	if (data->eaters != SEM_FAILED)
		sem_close(data->eaters);
	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_PRINT);
	sem_unlink(SEM_DEATH);
	sem_unlink(SEM_DONE);
	sem_unlink(SEM_EATERS);
	if (data->pids)
	{
		free(data->pids);
		data->pids = NULL;
	}
}
