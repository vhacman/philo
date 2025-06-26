/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:33:06 by vhacman           #+#    #+#             */
/*   Updated: 2025/06/26 14:37:30 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	parse_args(int ac, char **av, t_data *data)
{
	if (is_error(ac, av))
		return (1);
	data->num_philos = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data->meals_required = ft_atoi(ac[5]);
	else
		data->meals_required = -1;
	data->someone_died = 0;
	if (is_valid_time(data->num_philos)
		|| is_valid_time(data->time_to_die)
		|| is_valid_time(data->time_to_eat)
		|| is_valid_time(data->time_to_sleep)
		|| is_valid_meal(ac, data->meals_required))
	{
		printf("Error: invalid argument values\n");
		return (1);
	}
}

