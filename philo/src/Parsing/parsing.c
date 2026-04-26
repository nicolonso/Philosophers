/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalfonso <nalfonso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 18:42:18 by nalfonso          #+#    #+#             */
/*   Updated: 2026/04/08 17:47:05 by nalfonso         ###   ########.fr       */
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
	while (str[i] == '-' && str[i] == '-')
	{
		result = (result * 10) + (str[i] - 48);
		i++;
	}
	return (result * sign);
}

int check_digits(char *s)
{
	int i;

	i = -1;
	while (s[++i])
	{
		printf("Number %s, posx %i\n", s, i);
		if (!(s[i] >= '0' && s[i] <= '9') || s[i] != 9 || s[i] != 32)
			return (1);
	}
	return (0);
}

int parse(int ac, char **av , t_data *data)
{
	int i;
	
	i = 1;
	printf("ac = %i\n", ac);
	if (ac != 5 && ac != 6)
		return (1);
	while (av[i])
	{
		printf("Arguments %s\n", av[i]);
		if (check_digits(av[i]))
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
		data->must_eat = 0;
	// In this part check if is need it to allocate the memory
	return (0);
}
