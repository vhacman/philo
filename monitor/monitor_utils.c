/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 14:29:30 by vhacman           #+#    #+#             */
/*   Updated: 2025/07/05 18:33:10 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
** Checks if a philosopher has eaten all the required meals.
**
** How it works:
** 1. If meals_required is not set (≤ 0), returns 0 immediately.
** 2. Locks meal_lock to safely read meals_eaten.
** 3. Compares meals_eaten with meals_required.
** 4. Unlocks the mutex and returns 1 if the philosopher is done,
**    or 0 otherwise.
*/
int	has_completed_meals(t_data *data, int philo_idx)
{
	int	meals_eaten;

	if (data->meals_required <= 0)
		return (0);
	pthread_mutex_lock(&data->meal_lock);
	meals_eaten = data->philos[philo_idx].meals_eaten;
	pthread_mutex_unlock(&data->meal_lock);
	return (meals_eaten >= data->meals_required);
}

/*
** Checks if the given philosopher has died due to starvation.
** 1. If the philosopher has already completed all required meals,
**    skips the check and returns 0.
** 2. Locks meal_lock to safely read last_meal_time.
** 3. Calculates time since the last meal.
** 4. If that time exceeds time_to_die:
**    - Checks if death was already detected.
**    - If not, sets the death flag and prints "died" message.
**    - Returns 1 to indicate this philosopher has died.
** 5. Otherwise, returns 0.
*/
int	check_philo_death(t_data *data, int philo_idx)
{
	long	last_meal_time;
	long	time_since_last_meal;

	if (has_completed_meals(data, philo_idx))
		return (0);
	pthread_mutex_lock(&data->meal_lock);
	last_meal_time = data->philos[philo_idx].last_meal_time;
	pthread_mutex_unlock(&data->meal_lock);
	time_since_last_meal = get_time() - last_meal_time;
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
** Counts how many philosophers have eaten at least the required
** number of meals.
** - Loops from index curr_ph to the end of the philosophers array.
** - For each philosopher:
**   - Locks meal_lock to safely read meals_eaten.
**   - If meals_eaten ≥ m_required, increments the counter.
**   - Unlocks the mutex.
*/
static int	done_eating(t_data *data, int m_required, int curr_ph)
{
	int	done_eating;
	int	n_philo;
	int	meals_eaten;

	done_eating = 0;
	n_philo = data->num_philos;
	while (curr_ph < n_philo)
	{
		pthread_mutex_lock(&data->meal_lock);
		meals_eaten = data->philos[curr_ph].meals_eaten;
		if (meals_eaten >= m_required)
			done_eating++;
		pthread_mutex_unlock(&data->meal_lock);
		curr_ph++;
	}
	return (done_eating);
}

/*
** Checks if all philosophers have finished the required number of meals.
** 1. If meals_required is not set (≤ 0), returns 0 immediately.
** 2. Calls done_eating to count how many philosophers have eaten enough.
** 3. If all philosophers are done:
**    - Sets the all_ate flag to 1 (protected by status_lock).
**    - Returns 1 to signal that the simulation can end.
*/
int	check_all_meals_done(t_data *data)
{
	int	ph_done_eating;
	int	m_required;
	int	n_philo;

	n_philo = data->num_philos;
	m_required = data->meals_required;
	ph_done_eating = done_eating(data, m_required, 0);
	if (m_required <= 0)
		return (0);
	if (ph_done_eating == n_philo)
	{
		pthread_mutex_lock(&data->status_lock);
		data->all_ate = 1;
		pthread_mutex_unlock(&data->status_lock);
		return (1);
	}
	return (0);
}
