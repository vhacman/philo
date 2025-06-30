/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:57:47 by vhacman           #+#    #+#             */
/*   Updated: 2025/06/30 12:23:02 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
** Entry point of the program. It manages the simulation
** lifecycle of the philosophers. First, it parses the command-line
** arguments and initializes the simulation environment. If any step
** fails (parsing, initialization, thread creation), it ensures the
** proper cleanup of allocated resources before exiting with an error.
**
** Steps:
** 1. parse_args: Validates and stores input parameters into the data
**    structure.
** 2. init_simulation: Initializes all mutexes, philosophers, and shared
**    variables.
** 3. create_threads: Starts one thread per philosopher to simulate their
**    behavior.
** 4. pthread_create (monitor): Creates a separate thread to monitor the
**    death condition or completion of the simulation.
** 5. pthread_join: Waits for the monitor thread to finish.
** 6. join_threads: Waits for all philosopher threads to finish execution.
** 7. cleanup_simulation: Frees all allocated memory and destroys mutexes.
**
** Returns 0 on successful execution, 1 if any error occurs during setup.
*/
int	main(int ac, char **av)
{
	t_data	data;

	if (parse_args(ac, av, &data) != 0)
		return (1);
	if (init_simulation(&data) != 0)
	{
		cleanup_simulation(&data);
		return (1);
	}
	if (create_threads(&data) != 0)
	{
		cleanup_simulation(&data);
		return (1);
	}
	if (pthread_create(&data.monitor, NULL, monitor, &data) != 0)
	{
		printf("Error: monitor thread creation failed\n");
		cleanup_simulation(&data);
		return (1);
	}
	pthread_join(data.monitor, NULL);
	join_threads(&data);
	cleanup_simulation(&data);
	return (0);
}
