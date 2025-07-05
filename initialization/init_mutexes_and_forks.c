/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mutexes_and_forks.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 14:17:57 by vhacman           #+#    #+#             */
/*   Updated: 2025/07/05 19:04:58 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
** Initializes all shared mutexes in the data structure
** - print_lock: Synchronizes output to avoid overlapping prints
** - death_lock: Protects the someone_died flag
** - meal_lock: Protects access to meal-related data
** If any initialization fails, previously initialized mutexes are cleaned up
** using cleanup_mutexes().
*/
int	init_mutexes(t_data *data)
{
	if (pthread_mutex_init(&data->print_lock, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&data->death_lock, NULL) != 0)
	{
		pthread_mutex_destroy(&data->print_lock);
		return (1);
	}
	if (pthread_mutex_init(&data->meal_lock, NULL) != 0)
	{
		pthread_mutex_destroy(&data->print_lock);
		pthread_mutex_destroy(&data->death_lock);
		return (1);
	}
	return (0);
}

/*
** Allocates memory for the forks mutex array based on num_philos.
** Return: 0 on success, 1 on failure
*/
static int	allocate_forks(t_data *data)
{
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philos);
	if (!data->forks)
		return (1);
	return (0);
}

/*
** Initializes the forks (mutexes) for the simulation
** First allocates memory for the forks array, then initializes
** each mutex. If any step fails, does cleanup.
*/
int	init_forks(t_data *data)
{
	int	i;

	i = 0;
	if (allocate_forks(data) != 0)
		return (1);
	while (i < data->num_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
		{
			printf("Error: pthread mutex init fork\n");
			cleanup_forks(data);
			return (1);
		}
		i++;
	}
	return (0);
}
