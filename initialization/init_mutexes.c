/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mutexes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 14:17:57 by vhacman           #+#    #+#             */
/*   Updated: 2025/07/03 12:37:10 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
** Initializes a single mutex
** @mutex: Pointer to the mutex to initialize
** @name: Name of the mutex (used for error messages)
**
** Calls pthread_mutex_init() on the given mutex.
** If initialization fails, prints an error with the mutex name.
*/
int	init_single_mutex(pthread_mutex_t *mutex, char *name)
{
	if (pthread_mutex_init(mutex, NULL) != 0)
	{
		printf("Error: pthread mutex init%s\n", name);
		return (1);
	}
	return (0);
}

/*
** Initializes all shared mutexes in the data structure
** @data: Pointer to the simulation data structure
**
** Initializes the following mutexes:
** - print_lock: Synchronizes output to avoid overlapping prints
** - death_lock: Protects the someone_died flag
** - meal_lock: Protects access to meal-related data
**
** If any initialization fails, previously initialized mutexes are cleaned up
** using cleanup_mutexes().
*/
int	init_mutexes(t_data *data)
{
	if (init_single_mutex(&data->print_lock, "print_lock") != 0)
		return (1);
	if (init_single_mutex(&data->death_lock, "death_lock") != 0)
		return (cleanup_mutexes(data));
	if (init_single_mutex(&data->meal_lock, "meal_lock") != 0)
		return (cleanup_mutexes(data));
	return (0);
}
