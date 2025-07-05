/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:33:06 by vhacman           #+#    #+#             */
/*   Updated: 2025/07/05 19:07:22 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
** Checks whether the parsed arguments in the data struct are valid.
** is_valid_philos:
**    - Fails if the number of philosophers is less than 1.
**    - Prints an error and returns 1 if invalid.
** is_valid_time:
**    - Fails if any time values (die, eat, sleep) are ≤ 0.
** is_valid_meals:
**    - Fails if meals_required is present but ≤ 0.
**    - Only checked if ac == 6.
** If any value is invalid, prints an error and returns 1.
*/
static int	validate_arguments(int ac, t_data *data)
{
	if (is_valid_philos(data->num_philos))
	{
		printf(COLOR_RED "Error: philos must be at least 1" COLOR_RESET "\n");
		return (1);
	}
	if (is_valid_time(data->time_to_die)
		|| is_valid_time(data->time_to_eat)
		|| is_valid_time(data->time_to_sleep) || is_valid_meals(ac,
			data->meals_required))
	{
		printf(COLOR_RED "Error: invalid argument values" COLOR_RESET "\n");
		printf(COLOR_GREEN "Example: ./philo  num_philos  die  eat  sleep"
			COLOR_RESET "\n");
		printf(COLOR_GREEN "         ./philo      4       410  200  200"
			COLOR_RESET "\n");
		return (1);
	}
	return (0);
}

/*
** Parses and validates the command-line arguments. This function fills
** the 'data' structure with the input values if they are valid.
** 1. is_error: Checks if the number or format of arguments is incorrect.
** 2. ft_atoi: Converts argument strings to integers:
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
