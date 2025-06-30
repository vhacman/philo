/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:33:06 by vhacman           #+#    #+#             */
/*   Updated: 2025/06/30 12:25:00 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
** Parses and validates command-line arguments
** @ac: Argument count
** @av: Argument vector
** @data: Pointer to the simulation data structure
**
** Converts input strings to integers using ft_atoi:
** - av[1] = number of philosophers
** - av[2] = time to die (in milliseconds)
** - av[3] = time to eat (in milliseconds)
** - av[4] = time to sleep (in milliseconds)
** - av[5] (optional) = meals each philosopher must eat
**
** If 5 arguments are given, meals_required is set; otherwise, it is -1.
** Sets someone_died to 0 (used as a shared death flag).
** Returns 1 if input format is wrong or any value is invalid (e.g., <= 0).
** Returns 0 on successful parsing and value assignment.
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
	if (is_valid_time(data->num_philos) || is_valid_time(data->time_to_die)
		|| is_valid_time(data->time_to_eat)
		|| is_valid_time(data->time_to_sleep) || is_valid_meals(ac,
			data->meals_required))
	{
		printf("Error: invalid argument values\n");
		return (1);
	}
	return (0);
}
