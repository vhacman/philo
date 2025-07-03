/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_forks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 14:18:27 by vhacman           #+#    #+#             */
/*   Updated: 2025/07/03 12:35:52 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
** Allocates memory for the forks array
** @data: pointer to simulation data structure
**
** Allocates memory for the forks mutex array based on num_philos.
**
** Return: 0 on success, 1 on failure
*/
int	allocate_forks(t_data *data)
{
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philos);
	if (!data->forks)
	{
		printf("Error: malloc forks\n");
		return (1);
	}
	return (0);
}

/*
** Initializes the forks (mutexes) for the simulation
** @data: pointer to simulation data structure
**
** First allocates memory for the forks array, then initializes
** each mutex. If any step fails, performs cleanup.
**
** Return: 0 on success, 1 on failure
*/
int	init_forks(t_data *data)
{
	int	i;

	if (allocate_forks(data) != 0)
		return (1);
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
