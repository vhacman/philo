/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:57:47 by vhacman           #+#    #+#             */
/*   Updated: 2025/07/05 15:32:52 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
** Parses input arguments and initializes the simulation.
** Step-by-step:
** 1. parse_args: parses and validates arguments.
** 2. init_simulation: allocates memory and initializes data,
**    mutexes, and philosopher structures.
** 3. If anything fails, calls cleanup_simulation to free memory.
** Returns 0 on success, 1 on failure.
*/
int	setup_simulation(t_data *data, int ac, char **av)
{
	if (parse_args(ac, av, data) != 0)
		return (1);
	if (init_simulation(data) != 0)
	{
		cleanup_simulation(data);
		return (1);
	}
	return (0);
}

/*
** Starts the simulation by creating philosopher threads and the monitor.
** 1. create_threads: starts a thread for each philosopher.
** 2. create_monitor_thread: starts the thread that checks for death.
** 3. If any thread creation fails, cleans up and returns 1.
** Returns 0 on success, 1 on failure.
*/
int	run_simulation(t_data *data)
{
	if (create_threads(data) != 0)
	{
		cleanup_simulation(data);
		return (1);
	}
	if (create_monitor_thread(data) != 0)
	{
		cleanup_simulation(data);
		return (1);
	}
	return (0);
}

/*
** Final step of the program. Waits for all threads to finish and frees memory.
** 1. Waits for the monitor thread to finish with pthread_join.
** 2. Calls join_threads to wait for all philosopher threads.
** 3. Frees all allocated resources and destroys mutexes.
** Returns 0 always (simulation ends here).
*/
int	finalize_simulation(t_data *data)
{
	pthread_join(data->monitor, NULL);
	join_threads(data);
	cleanup_simulation(data);
	return (0);
}

/*
** Entry point of the program. It manages the full simulation flow.
**
** Returns 0 on success, 1 on error.
*/
int	main(int ac, char **av)
{
	t_data	data;

	if (setup_simulation(&data, ac, av) != 0)
		return (1);
	if (run_simulation(&data) != 0)
		return (1);
	finalize_simulation(&data);
	return (0);
}
