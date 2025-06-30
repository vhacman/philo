/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:10:57 by vhacman           #+#    #+#             */
/*   Updated: 2025/06/30 12:31:26 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
** Sets the death flag to signal simulation stop
** @data: Pointer to the simulation data structure
**
** Locks the death_lock mutex, sets someone_died to 1,
** then unlocks the mutex. This flag is used to stop all threads.
*/
void	set_death(t_data *data)
{
	pthread_mutex_lock(&data->death_lock);
	data->someone_died = 1;
	pthread_mutex_unlock(&data->death_lock);
}

/*
** Checks if any philosopher has died
** @data: Pointer to the simulation data structure
**
** Locks the death_lock mutex to safely read someone_died.
** Returns 1 if a death was detected, 0 otherwise.
*/
int	check_death(t_data *data)
{
	int	is_anyone_dead;

	pthread_mutex_lock(&data->death_lock);
	is_anyone_dead = data->someone_died;
	pthread_mutex_unlock(&data->death_lock);
	return (is_anyone_dead);
}
