/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mutexes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 14:17:57 by vhacman           #+#    #+#             */
/*   Updated: 2025/06/26 15:36:00 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int init_single_mutex(pthread_mutex_t *mutex, char *name)
{
	if (pthread_mutex_init(mutex, NULL) != 0)
	{
		printf("Error: pthread mutex init%s\n", name);
		return (1);
	}
	return (0);
}

int init_mutexes(t_data *data)
{
	if (init_single_mutex(&data->print_lock, "print_lock") != 0)
		return (1);
	if (init_single_mutex(&data->death_lock, "death_lock") != 0)
		return(cleanup_mutexes(data));
	if(init_single_mutex(&data->meal_lock, "meal_lock") != 0)
		return (cleanup_mutexes(data));
	return (0);
}
