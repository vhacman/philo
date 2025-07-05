/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:07:59 by vhacman           #+#    #+#             */
/*   Updated: 2025/07/05 19:04:10 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
** Frees philosopher array
** Sets pointer to NULL to avoid dangling references.
*/
static void	cleanup_philos(t_data *data)
{
	if (data->philos)
	{
		free(data->philos);
		data->philos = NULL;
	}
}

/*
** Destroys all shared mutexes
** print_lock, death_lock and meal_lock
** Return: Always returns 1 to indicate cleanup ok
*/
static int	cleanup_mutexes(t_data *data)
{
	pthread_mutex_destroy(&data->print_lock);
	pthread_mutex_destroy(&data->death_lock);
	pthread_mutex_destroy(&data->meal_lock);
	return (1);
}

/*
** Frees all simulation resources
*/
void	cleanup_simulation(t_data *data)
{
	cleanup_philos(data);
	cleanup_forks(data);
	cleanup_mutexes(data);
}

/*
** Destroys and frees all fork mutexes.
**  Iterate over each fork mutex:
**    - Attempt to destroy it with pthread_mutex_destroy.
**    - If any destruction fails, set error flag to 1.
**  After destroying all mutexes, free the forks array.
**  Set the forks pointer to NULL to avoid dangling access.
*/
int	cleanup_forks(t_data *data)
{
	int	i;
	int	error;

	error = 0;
	i = 0;
	if (!data->forks)
		return (0);
	while (i < data->num_philos)
	{
		if (pthread_mutex_destroy(&data->forks[i]) != 0)
			error = 1;
		i++;
	}
	free(data->forks);
	data->forks = NULL;
	return (error);
}

/*
** Partially frees resources based on failure stage
** Stage 2: Frees forks and mutexes
** Stage 1: Only destroys mutexes
*/
int	cleanup_simulation_stage(t_data *data, int stage)
{
	if (stage >= 2)
		cleanup_forks(data);
	if (stage >= 1)
	{
		cleanup_mutexes(data);
		return (1);
	}
	return (0);
}
