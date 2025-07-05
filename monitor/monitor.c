/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 17:40:35 by vhacman           #+#    #+#             */
/*   Updated: 2025/07/05 16:43:16 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
** Monitors the simulation to detect philosopher death or completion.
** Enters a loop that runs while no philosopher has died.
** If all meals are done, exits the monitor.
** Iterates over all philosophers:
** -Checks if any philosopher has died.
** -If so, exits immediately.
**  Sleeps briefly (100 µs) to reduce CPU usage.
** Ensures simulation ends when a philosopher dies or all are done.
** Returns: NULL when the monitor exits.
*/
void	*monitor(void *philo)
{
	t_data	*data;
	int		curr_philo_index;

	data = (t_data *)philo;
	while (!check_if_is_dead(data))
	{
		if (check_all_meals_done(data))
			return (NULL);
		curr_philo_index = 0;
		while (curr_philo_index < data->num_philos)
		{
			if (check_philo_death(data, curr_philo_index))
				return (NULL);
			curr_philo_index++;
		}
		usleep(100);
	}
	return (NULL);
}
