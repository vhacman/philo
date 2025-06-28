/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 14:29:30 by vhacman           #+#    #+#             */
/*   Updated: 2025/06/28 20:58:39 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_philo_death(t_data *data, int philo_idx)
{
	long	current_time;
	long	time_of_last_meal;
	long	time_since_last_meal;

	// ———————————————— controllo vittoria: tutti hanno mangiato "meals_required" volte?
	if (data->meals_required > 0)
	{
		int done = 0;
		for (int i = 0; i < data->num_philos; i++)
		{
			pthread_mutex_lock(&data->meal_lock);
			if (data->philos[i].meals_eaten >= data->meals_required)
				done++;
			pthread_mutex_unlock(&data->meal_lock);
		}
		if (done == data->num_philos)
		{
			set_death(data);
			return (1);
		}
	}

	// ———————————————— controllo morte per fame del filosofo corrente
	current_time = get_time();
	pthread_mutex_lock(&data->meal_lock);
	time_of_last_meal = data->philos[philo_idx].last_meal_time;
	pthread_mutex_unlock(&data->meal_lock);

	time_since_last_meal = current_time - time_of_last_meal;
	if (time_since_last_meal > data->time_to_die)
	{
		if (!check_death(data))
		{
			set_death(data);
			print_philo_status(&data->philos[philo_idx], "died");
		}
		  // se non è già terminata la simulazione con morte
        if (!check_death(data))
        {
            set_death(data);  // imposta someone_died = 1
            print_philo_status(&data->philos[philo_idx], "died");
        }
		return (1);
	}
	return (0);
}


int	check_all_meals_done(t_data *data)
{
	int	curr_philo_index;
	int	done_eating;

	// CASO SPECIALE: Se non c'è un limite di pasti, la simulazione non finisce mai così
	if (data->meals_required <= 0)
		return (0);
	done_eating = 0;
	curr_philo_index = 0;
	// Controlla ogni filosofo per vedere se ha raggiunto il numero richiesto di pasti
	while (curr_philo_index < data->num_philos)
	{
		pthread_mutex_lock(&data->meal_lock);
		// Se questo filosofo ha mangiato abbastanza, incrementa il contatore
		if (data->philos[curr_philo_index].meals_eaten >= data->meals_required)
			done_eating++;
		pthread_mutex_unlock(&data->meal_lock);
		curr_philo_index++;
	}
	// CONDIZIONE DI VITTORIA: Se tutti hanno finito di mangiare
	if (done_eating == data->num_philos)
	{
		pthread_mutex_lock(&data->status_lock);
	data->all_ate = 1;
	pthread_mutex_unlock(&data->status_lock);
	return (1); // esci dal monitor
	}
	return (0);
}
