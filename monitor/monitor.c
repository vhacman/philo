/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 17:40:35 by vhacman           #+#    #+#             */
/*   Updated: 2025/06/28 20:16:14 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor(void	*philo)
{
	t_data	*data;
	int		curr_philo_index;

	data = (t_data *)philo;
	while(!check_death(data))
	{
		if(check_all_meals_done(data))
			return (NULL);
		// CONTROLLO MORTE: Esamina ogni filosofo per vedere se è morto di fame
		curr_philo_index = 0;
		while(curr_philo_index < data->num_philos
			&& !check_death(data))
		{
			if(check_philo_death(data, curr_philo_index))
				return (NULL);
			curr_philo_index++;
		}
		//riposa per non saturare CPU
		usleep(1000);
	}
	return (NULL);
}
