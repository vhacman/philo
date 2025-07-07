/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 14:29:30 by vhacman           #+#    #+#             */
/*   Updated: 2025/07/07 11:55:07 by vhacman          ###   ########.fr       */
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
** Checks if the specified philosopher has died of starvation.
** 1. If the philosopher has already completed all required meals,
**    or if a death has already been detected globally, return 0.
** 2. Lock the meal mutex to read the philosopher's last_meal_time.
** 3. Calculate how much time has passed since their last meal.
** 4. If the elapsed time exceeds time_to_die:
**    - Mark global death flag using set_death.
**    - Print "died" message with timestamp.
**    - Return 1 to indicate death.
** 5. If the philosopher is still alive, return 0.*/
int	check_philo_death(t_data *data, int philo_idx)
{
	long	time_since_last_meal;

	if (has_completed_meals(data, philo_idx) || check_if_is_dead(data))
		return (0);
	pthread_mutex_lock(&data->meal_lock);
	time_since_last_meal = get_time() - data->philos[philo_idx].last_meal_time;
	pthread_mutex_unlock(&data->meal_lock);
	if (time_since_last_meal > data->time_to_die)
	{
		set_death(data);
		print_philo_status(&data->philos[philo_idx], "died");
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
