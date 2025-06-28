/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:07:59 by vhacman           #+#    #+#             */
/*   Updated: 2025/06/28 20:05:17 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void cleanup_simulation(t_data *data)
{
	cleanup_philos(data);
	cleanup_forks(data);
	cleanup_mutexes(data);
}

int cleanup_mutexes(t_data *data)
{
	pthread_mutex_destroy(&data->print_lock);
	pthread_mutex_destroy(&data->death_lock);
	pthread_mutex_destroy(&data->meal_lock);
	return (1);
}

int cleanup_forks(t_data *data)
{
	int i;
	int error;

	error = 0;
	if (data->forks)
	{
		i = 0;
		while (i < data->num_philos)
		{
			if (pthread_mutex_destroy(&data->forks[i]) != 0)
                error = 1;
			i++;
		}
		free(data->forks);
		data->forks = NULL;
	}
	return (error);
}

void cleanup_philos(t_data *data)
{
	if (data->philos)
	{
		free(data->philos);
		data->philos = NULL;
	}
}

int cleanup_simulation_stage(t_data *data, int stage)
{
	if (stage >= 3)  // Se hai allocato philos, liberali
		cleanup_philos(data);
	if (stage >= 2)  // Se hai inizializzato forks, distruggili
		cleanup_forks(data);
	if (stage >= 1)  // Se hai inizializzato mutex, distruggili
	{
		cleanup_mutexes(data);
		return (1);
	}
	return (0);
}
