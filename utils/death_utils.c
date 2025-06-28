/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:10:57 by vhacman           #+#    #+#             */
/*   Updated: 2025/06/28 19:18:12 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_death(t_data *data)
{
	pthread_mutex_lock(&data->death_lock);
	data->someone_died = 1;
	pthread_mutex_unlock(&data->death_lock);
}

/*Il mutex garantisce che solo un thread alla volta possa
leggere o scrivere someone_died, evitando confusione e errori.*/
int	check_death(t_data *data)
{
	int	is_anyone_dead;

	pthread_mutex_lock(&data->death_lock);
	is_anyone_dead = data->someone_died;
	pthread_mutex_unlock(&data->death_lock);
	return (is_anyone_dead);
}

