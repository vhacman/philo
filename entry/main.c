/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:57:47 by vhacman           #+#    #+#             */
/*   Updated: 2025/06/28 20:02:31 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int ac, char **av)
{
	t_data  data;

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
