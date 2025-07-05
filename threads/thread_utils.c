/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 14:15:19 by vhacman           #+#    #+#             */
/*   Updated: 2025/07/05 19:11:07 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
** Creates the monitor thread for the simulation
** @data: Pointer to the simulation data structure
*/
int	create_monitor_thread(t_data *data)
{
	if (pthread_create(&data->monitor, NULL, monitor, data) != 0)
		return (cleanup_simulation(data), 1);
	return (0);
}

/*
** Creates a thread for each philosopher
** Sets the start_time of the simulation and assigns this time as the
** initial last_meal_time for each philosopher.
** Calls pthread_create to launch the philo_routine for each philosopher.
*/
int	create_threads(t_data *data)
{
	int	i;

	data->start_time = get_time();
	i = 0;
	while (i < data->num_philos)
	{
		data->philos[i].last_meal_time = data->start_time;
		if (pthread_create(&data->philos[i].thread, NULL, philo_routine,
				&data->philos[i]) != 0)
			return (1);
		i++;
	}
	return (0);
}

/*
** Joins all philosopher threads
** Waits for each philosopher thread to finish using pthread_join().
** Ensures proper thread cleanup at the end of the simulation.
** Return: Always returns 0
*/
int	join_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
		pthread_join(data->philos[i++].thread, NULL);
	return (0);
}
