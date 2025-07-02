/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 14:29:30 by vhacman           #+#    #+#             */
/*   Updated: 2025/07/02 11:43:08 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
** Checks if a specific philosopher has eaten the required number of meals.
** This check is only performed if 'meals_required' > 0 (i.e., the optional
** argument was provided). The value is protected by a mutex to avoid race
** conditions during concurrent access.
**
** Step-by-step:
** 1. If no meal limit is set (meals_required <= 0), returns 0 immediately.
** 2. Locks meal_lock to safely access shared meals_eaten data.
** 3. Compares the meals eaten by the philosopher at index 'philo_idx'
**    to the meals_required threshold.
** 4. Unlocks the mutex and returns 1 if completed, 0 otherwise.
**
** Arguments:
** - data: pointer to the main simulation data
** - philo_idx: index of the philosopher in the data->philos array
**
** Returns 1 if the philosopher has finished all meals, 0 otherwise.
*/
int	has_completed_meals(t_data *data, int philo_idx)
{
	int	already_done;

	if (data->meals_required <= 0)
		return (0);
	pthread_mutex_lock(&data->meal_lock);
	already_done = (data->meals_required > 0
			&& data->philos[philo_idx].meals_eaten >= data->meals_required);
	pthread_mutex_unlock(&data->meal_lock);
	return (already_done);
}

/*
** Checks if a philosopher has died
** @data: Pointer to the simulation data structure
** @philo_idx: Index of the philosopher to check
**
** Skips the check if the philosopher has already eaten the required meals.
** Calculates the time since the last meal.
** If this time exceeds time_to_die and no death has been flagged yet,
** sets the death flag and prints that the philosopher died.
**
** Return: 1 if the philosopher died, 0 otherwise
*/
int	check_philo_death(t_data *data, int philo_idx)
{
	long	current_time;
	long	time_of_last_meal;
	long	time_since_last_meal;

	if (has_completed_meals(data, philo_idx))
		return (0);
	current_time = get_time();
	pthread_mutex_lock(&data->meal_lock);
	time_of_last_meal = data->philos[philo_idx].last_meal_time;
	pthread_mutex_unlock(&data->meal_lock);
	time_since_last_meal = current_time - time_of_last_meal;
	if (time_since_last_meal > data->time_to_die)
	{
		if (!check_if_is_dead(data))
		{
			set_death(data);
			print_philo_status(&data->philos[philo_idx], "died");
		}
		return (1);
	}
	return (0);
}

/*
** Checks if all philosophers have finished eating
** @data: Pointer to the simulation data structure
**
** Only active if meals_required > 0.
** Iterates through all philosophers and counts how many have reached
** the required number of meals. Uses a mutex to read meals_eaten safely.
** If all philosophers are done eating, sets all_ate to 1.
**
** Return: 1 if all meals are done, 0 otherwise
*/
int	check_all_meals_done(t_data *data)
{
	int	curr_philo_index;
	int	done_eating;

	if (data->meals_required <= 0)
		return (0);
	done_eating = 0;
	curr_philo_index = 0;
	while (curr_philo_index < data->num_philos)
	{
		pthread_mutex_lock(&data->meal_lock);
		if (data->philos[curr_philo_index].meals_eaten >= data->meals_required)
			done_eating++;
		pthread_mutex_unlock(&data->meal_lock);
		curr_philo_index++;
	}
	if (done_eating == data->num_philos)
	{
		pthread_mutex_lock(&data->status_lock);
		data->all_ate = 1;
		pthread_mutex_unlock(&data->status_lock);
		return (1);
	}
	return (0);
}
