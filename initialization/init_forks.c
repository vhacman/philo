/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_forks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 14:18:27 by vhacman           #+#    #+#             */
/*   Updated: 2025/06/26 16:05:01 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int init_forks(t_data *data)
{
	int i;

	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philos);
	if(!data->forks)
	{
		printf("Error: mallof forks\n");
		return (1);
	}
	i = 0;
	while(i < data->num_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
		{
			printf("Error: pthread mutex init fork\n", i);
			cleanup_forks(data);
			return (1);
		}
	}
	i++;
}
