/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:58:01 by vhacman           #+#    #+#             */
/*   Updated: 2025/06/30 12:27:34 by vhacman          ###   ########.fr       */
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
** Initializes the simulation environment
** @data: Pointer to the simulation data structure
**
** 1. Initializes all shared mutexes (init_mutexes).
** 2. Allocates memory and initializes fork mutexes (init_forks).
** 3. Initializes flags: someone_died and all_ate to 0.
** 4. Initializes status_lock mutex for shared state protection.
** 5. Allocates memory for philosopher structures (data->philos).
** 6. Calls initialize_data() to set per-philosopher values.
**
** On failure, performs partial cleanup using cleanup_simulation_stage().
** Return: 0 on success, 1 on error.
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
