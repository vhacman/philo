/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:58:01 by vhacman           #+#    #+#             */
/*   Updated: 2025/07/05 19:06:28 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
** Initializes the simulation state and status mutex
** Sets initial values for simulation flags and initializes
** the status mutex for thread-safe status updates.
** Return: 0 on success, cleanup stage number on failure
*/
static int	initialize_simulation_state(t_data *data)
{
	data->someone_died = 0;
	data->all_ate = 0;
	if (pthread_mutex_init(&data->status_lock, NULL) != 0)
		return (cleanup_simulation_stage(data, 1));
	return (0);
}

/*
** Allocates memory for the philosophers array based on num_philos.
** Return: 0 on success, cleanup stage number on failure
*/
static int	allocate_philosophers(t_data *data)
{
	data->philos = malloc(sizeof(t_philo) * data->num_philos);
	if (!data->philos)
		return (cleanup_simulation_stage(data, 2));
	return (0);
}

/*
** Initializes the internal state of each philosopher in the simulation.
**
** For each philosopher (from index 0 to num_philos - 1):
** - Sets a unique ID (starting from 1).
** - Initializes meals_eaten to 0 (no meals consumed yet).
** - Sets last_meal_time to 0.
** - Assigns left_fork to forks[i].
** - Assigns right_fork to forks[(i + 1) % num_philos] to ensure circular
**   fork sharing (the last philosopher wraps around to forks[0]).
** - Stores a pointer to the shared t_data structure for global access.
** Return: Always returns 0 (no failure conditions expected here).
*/
static int	initialize_data(t_data *data)
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
** Initializes the complete simulation
** Performs all initialization steps in order:
** 1. Initialize mutexes
** 2. Initialize forks
** 3. Initialize simulation state
** 4. Allocate philosophers array
** 5. Initialize data structures
** Return: 0 on success, cleanup stage number on failure
*/
int	init_simulation(t_data *data)
{
	if (init_mutexes(data) != 0)
		return (1);
	if (init_forks(data) != 0)
		return (cleanup_simulation_stage(data, 1));
	if (initialize_simulation_state(data) != 0)
		return (cleanup_simulation_stage(data, 1));
	if (allocate_philosophers(data) != 0)
		return (cleanup_simulation_stage(data, 2));
	initialize_data(data);
	return (0);
}
