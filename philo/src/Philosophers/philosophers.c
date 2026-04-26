/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalfonso <nalfonso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 21:58:16 by nalfonso          #+#    #+#             */
/*   Updated: 2026/04/08 17:31:04 by nalfonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	main(int ac, char **av)
{
	t_data 	data;
	//t_philo	philo;

	if (parse(ac, av, &data))
	{
		printf("Parametrers are incorrect\n");
		return (1);
	}
	return (0);
}
