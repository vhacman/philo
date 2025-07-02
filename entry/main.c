/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:57:47 by vhacman           #+#    #+#             */
/*   Updated: 2025/07/02 11:27:51 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
** Entry point of the program. It parses the command-line
** arguments and initializes all simulation data. If parsing,
** initialization, or thread creation fails, it performs cleanup
** and exits with error code 1. Otherwise, it launches a monitor
** thread to track simulation completion or philosopher death,
** joins all threads, and finally frees resources.
**
** Steps:
** 1. parse_args: Parses and validates arguments, fills the data struct.
** 2. init_simulation: Sets up mutexes and simulation structures.
** 3. create_threads: Starts a thread per philosopher.
** 4. pthread_create (monitor): Spawns a thread to monitor simulation.
** 5. pthread_join: Waits for monitor thread to finish.
** 6. join_threads: Waits for all philosopher threads to terminate.
** 7. cleanup_simulation: Destroys mutexes and frees all memory.
**
** Returns 0 on success, 1 on any failure during setup or thread creation.
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
