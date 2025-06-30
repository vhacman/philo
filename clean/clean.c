/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:07:59 by vhacman           #+#    #+#             */
/*   Updated: 2025/06/30 12:29:28 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
** Frees all simulation resources
** @data: Pointer to the simulation data structure
**
** Calls cleanup functions in this order:
** - cleanup_philos: Frees philosopher array
** - cleanup_forks: Frees and destroys fork mutexes
** - cleanup_mutexes: Destroys global/shared mutexes
*/
void	cleanup_simulation(t_data *data)
{
	cleanup_philos(data);
	cleanup_forks(data);
	cleanup_mutexes(data);
}

/*
** Destroys all shared mutexes
** @data: Pointer to the simulation data structure
**
** Destroys the following mutexes:
** - print_lock
** - death_lock
** - meal_lock
**
** Return: Always returns 1 to indicate cleanup was performed
*/
int	cleanup_mutexes(t_data *data)
{
	pthread_mutex_destroy(&data->print_lock);
	pthread_mutex_destroy(&data->death_lock);
	pthread_mutex_destroy(&data->meal_lock);
	return (1);
}

/*
** Destroys and frees fork mutexes
** @data: Pointer to the simulation data structure
**
** Destroys each fork mutex in the forks array.
** Frees the array and sets pointer to NULL.
** Tracks and returns any error from pthread_mutex_destroy().
**
** Return: 1 if at least one mutex failed to destroy, 0 otherwise
*/
int	cleanup_forks(t_data *data)
{
	int	i;
	int	error;

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

/*
** Frees philosopher array
** @data: Pointer to the simulation data structure
**
** Frees the memory allocated for philosopher structures.
** Sets pointer to NULL to avoid dangling references.
*/
void	cleanup_philos(t_data *data)
{
	if (data->philos)
	{
		free(data->philos);
		data->philos = NULL;
	}
}

/*
** Partially frees resources based on failure stage
** @data: Pointer to the simulation data structure
** @stage: Indicates which resources were successfully initialized
**
** Stage 3 or higher: Frees philosophers, forks, and mutexes
** Stage 2: Frees forks and mutexes
** Stage 1: Only destroys mutexes
**
** Return: 1 if cleanup occurred, 0 otherwise
*/
int	cleanup_simulation_stage(t_data *data, int stage)
{
	if (stage >= 3)
		cleanup_philos(data);
	if (stage >= 2)
		cleanup_forks(data);
	if (stage >= 1)
	{
		cleanup_mutexes(data);
		return (1);
	}
	return (0);
}
