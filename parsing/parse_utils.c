/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 14:33:45 by vhacman           #+#    #+#             */
/*   Updated: 2025/07/03 12:18:34 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
** Checks for errors in the input arguments
** Verifies that the number of arguments is 5 or 6.
** Then checks that each argument (from av[1] to av[ac - 1]) is numeric
** using is_number(). If any check fails, prints an error and returns 1.
*/
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

/*
** Validates time-related input values
** @value: Integer value to check
** Used to validate number of philosophers and time parameters.
** A value is considered invalid if it is less than or equal to 0.
*/
int	is_valid_time(int value)
{
	return (value <= 0);
}

/*
** Validates the meals_required argument
** @meals: Parsed number of meals required
** Only called if 6 arguments are provided.
** Checks that the meals_required value is strictly greater than 0.
*/
int	is_valid_meals(int ac, int meals)
{
	return (ac == 6 && meals <= 0);
}
