/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalfonso <nalfonso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 21:58:16 by nalfonso          #+#    #+#             */
/*   Updated: 2026/04/27 22:09:46 by nalfonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	main(int ac, char **av)
{
	t_data 	data;
	//t_philo	philo;

	if (parse(ac, av, &data))
	{
		write (stderr, "Parametrers are incorrect\n", 27);
		return (1);
	}
	return (0);
}
