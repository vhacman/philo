/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 14:33:45 by vhacman           #+#    #+#             */
/*   Updated: 2025/07/05 18:47:50 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_error(int ac, char **av)
{
	int	i;

	i = 1;
	if (ac != 5 && ac != 6)
	{
		print_usage_error();
		return (1);
	}
	while (i < ac)
	{
		if (!is_number(av[i]))
		{
			print_numeric_error();
			return (1);
		}
		i++;
	}
	return (0);
}

int	is_valid_time(int value)
{
	return (value <= 0);
}

int	is_valid_meals(int ac, int meals)
{
	return (ac == 6 && meals <= 0);
}

int	is_valid_philos(int n_philos)
{
	return (n_philos <= 0);
}
