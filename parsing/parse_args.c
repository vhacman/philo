/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:33:06 by vhacman           #+#    #+#             */
/*   Updated: 2025/07/04 14:44:48 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
** Checks whether the parsed arguments in the data struct are valid.
** 1. is_valid_philos:
**    - Fails if the number of philosophers is less than 1.
**    - Prints an error and returns 1 if invalid.
** 2. is_valid_time:
**    - Fails if any time values (die, eat, sleep) are ≤ 0.
** 3. is_valid_meals:
**    - Fails if meals_required is present but ≤ 0.
**    - Only checked if ac == 6.
** 4. If any value is invalid, prints an error and returns 1.
*/
int	validate_arguments(int ac, t_data *data)
{
	if (is_valid_philos(data->num_philos))
	{
		printf("Error: philos must be at least 1\n");
		return (1);
	}
	if (is_valid_time(data->time_to_die)
		|| is_valid_time(data->time_to_eat)
		|| is_valid_time(data->time_to_sleep) || is_valid_meals(ac,
			data->meals_required))
	{
		printf("Error: invalid argument values\n");
		return (1);
	}
	return (0);
}

/*
** Parses and validates the command-line arguments. This function fills
** the 'data' structure with the input values if they are valid.
**
** Step-by-step:
** 1. is_error: Checks if the number or format of arguments is incorrect.
**    Returns 1 immediately if any error is found.
** 2. ft_atoi: Converts argument strings to integers:
**    - av[1] -> number of philosophers
**    - av[2] -> time to die (ms)
**    - av[3] -> time to eat (ms)
**    - av[4] -> time to sleep (ms)
**    - av[5] -> (optional) number of meals each philosopher must eat
** 3. If av[5] is not provided, sets meals_required to -1 (infinite).
** 4. Sets someone_died flag to 0 as default.
** 5. Validates that all time and meal values are positive using:
**    validate_arguments
*/
int	parse_args(int ac, char **av, t_data *data)
{
	if (is_error(ac, av))
		return (1);
	data->num_philos = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data->meals_required = ft_atoi(av[5]);
	else
		data->meals_required = -1;
	data->someone_died = 0;
	if (validate_arguments(ac, data))
		return (1);
	return (0);
}
