/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:58:01 by vhacman           #+#    #+#             */
/*   Updated: 2025/07/02 11:30:19 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
** Initializes philosopher-specific data
** @data: Pointer to the simulation data structure
**
** For each philosopher:
** - Assigns a unique ID starting from 1
** - Initializes meals_eaten and last_meal_time to 0
** - Assigns left and right fork pointers (circular arrangement)
** - Stores a pointer to the shared data structure
**
** Return: Always returns 0 (no error handling needed here)
*/
int	initialize_data(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].meals_eaten = 0;
		data->philos[i].last_meal_time = 0;
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = &data->forks[(i + 1) % data->num_philos];
		data->philos[i].data = data;
		i++;
	}
	return (0);
}

/*
** Initializes the simulation environment. This function sets up
** all required data and synchronization primitives before starting
** the threads.
**
** Step-by-step:
** 1. init_mutexes: Initializes global mutexes used in the simulation.
**    If it fails, returns 1 immediately.
** 2. init_forks: Allocates and initializes fork mutexes.
**    If it fails, calls cleanup_simulation_stage(data, 1) and returns 1.
** 3. Initializes 'someone_died' and 'all_ate' flags to 0.
** 4. Initializes 'status_lock', a mutex used to protect shared state.
**    If it fails, cleans up forks and mutexes (stage 1) and returns 1.
** 5. Allocates memory for the philosophers array.
**    If allocation fails, cleans up forks, mutexes, and status_lock (stage 2).
** 6. initialize_data: Fills philosopher structures with initial values.
**
** Arguments:
** - data: pointer to main simulation data structure
**
** Returns 0 on success, 1 on any initialization failure.
*/
int	init_simulation(t_data *data)
{
	if (init_mutexes(data) != 0)
		return (1);
	if (init_forks(data) != 0)
		return (cleanup_simulation_stage(data, 1));
	data->someone_died = 0;
	data->all_ate = 0;
	if (pthread_mutex_init(&data->status_lock, NULL) != 0)
		return (cleanup_simulation_stage(data, 1));
	data->philos = malloc(sizeof(t_philo) * data->num_philos);
	if (!data->philos)
		return (cleanup_simulation_stage(data, 2));
	initialize_data(data);
	return (0);
}
