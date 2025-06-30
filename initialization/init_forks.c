/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_forks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 14:18:27 by vhacman           #+#    #+#             */
/*   Updated: 2025/06/30 12:29:52 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
** Allocates and initializes fork mutexes
** @data: Pointer to the simulation data structure
**
** Allocates an array of mutexes, one for each philosopher.
** Initializes each mutex with pthread_mutex_init().
** If allocation or initialization fails, prints an error,
** frees already initialized forks using cleanup_forks(),
** and returns 1.
**
** Return: 0 on success, 1 on failure
*/
int	init_forks(t_data *data)
{
	int	i;

	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philos);
	if (!data->forks)
	{
		printf("Error: mallof forks\n");
		return (1);
	}
	i = 0;
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
