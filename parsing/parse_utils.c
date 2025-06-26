/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 14:33:45 by vhacman           #+#    #+#             */
/*   Updated: 2025/06/26 14:34:56 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_error(int ac, char **av)
{
	int	i;

	i = 1;
	if (ac != 5 && ac != 6)
	{
		printf("Error: wrong n of args\n");
		return (1);
	}
	while (i < ac)
	{
		if (!is_number(av[i]))
		{
			printf("Error: args must be numeric");
			return (1);
		}
		i++;
	}
	return (0);
}

int is_valid_time(int value)
{
    return (value <= 0);
}

int is_valid_meals(int ac, int meals)
{
    return (ac == 6 && meals <= 0);
}
