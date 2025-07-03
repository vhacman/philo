/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 14:15:19 by vhacman           #+#    #+#             */
/*   Updated: 2025/07/03 12:30:37 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
** Creates a thread for each philosopher
** @data: Pointer to the simulation data structure
**
** Sets the start_time of the simulation and assigns this time as the
** initial last_meal_time for each philosopher.
** Calls pthread_create to launch the philo_routine for each philosopher.
** If thread creation fails, prints an error and returns 1.
**
** Return: 0 on success, 1 on failure
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
		{
			printf("Error: thread creation failed\n");
			return (1);
		}
		i++;
	}
	return (0);
}

/*
** Joins all philosopher threads
** @data: Pointer to the simulation data structure
**
** Waits for each philosopher thread to finish using pthread_join().
** Ensures proper thread cleanup at the end of the simulation.
**
** Return: Always returns 0
*/
int	join_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
	return (0);
}
