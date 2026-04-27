/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalfonso <nalfonso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 18:42:18 by nalfonso          #+#    #+#             */
/*   Updated: 2026/04/27 21:54:14 by nalfonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	ft_itoal(char *str)
{
	unsigned int	i;
	long			result;
	long			sign;

	i = 0;
	result = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i]<= 13) || str[i] == 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -sign;
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		result = (result * 10) + (str[i] - 48);
		i++;
	}
	return (result * sign);
}

int check_digits(char *s, int counter)
{
	int	i;

	i = 0;
	while (s[i] == 9 || s[i] == 32)
		i++;
	if (!s[i])
		return (1);
	while (s[i])
	{
		if (s[i] < 48 || s[i] > 57)
			return (1);
		i++;	
	}
	if (counter == 1 && ft_itoal(s) < 1)
		return (1);
	else if (counter > 1 && ft_itoal(s) < 0)
		return (1);
	return (0);
}

int parse(int ac, char **av , t_data *data)
{
	int i;
	
	i = 1;
	if (ac != 5 && ac != 6)
		return (1);
	while (av[i])
	{
		if (check_digits(av[i], i))
			return (1);
		i++;
	}
	data->nb_philo = ft_itoal(av[1]);
	data->time_to_die = ft_itoal(av[2]);
	data->time_to_eat = ft_itoal(av[3]);
	data->time_to_sleep = ft_itoal(av[4]);
	if (ac == 6)
	data->must_eat = ft_itoal(av[5]);
	else
	data->must_eat = -1;
	// In this part check if is need it to allocate the memory
	//printf("Arguments %i, %li, %li, %li, %i\n", data->nb_philo, data->time_to_die, data->time_to_eat, data->time_to_sleep, data->must_eat);
	return (0);
}
