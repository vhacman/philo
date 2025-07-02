/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 17:40:35 by vhacman           #+#    #+#             */
/*   Updated: 2025/07/02 09:50:07 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
** Monitors the simulation for death or completion
** @philo: Pointer to the shared simulation data (cast to t_data*)
**
** Repeatedly checks if:
** - Any philosopher has died (check_philo_death)
** - All philosophers have finished eating (check_all_meals_done)
**
** If a philosopher dies or all meals are done, exits the loop and returns.
** Sleeps briefly (100 microseconds) between checks to reduce CPU usage.
**
** Return: NULL (used as a thread routine)
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
