/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 11:45:32 by vhacman           #+#    #+#             */
/*   Updated: 2025/07/05 19:08:17 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
** Updates philosopher's last meal time and meal count
** @philo: Pointer to the philosopher struct
**
** Locks the meal_lock mutex to safely update:
** - last_meal_time: current time in milliseconds
** - meals_eaten: incremented by 1
** Unlocks the mutex after updating.
*/
static void	update_meal_time(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->meal_lock);
	philo->last_meal_time = get_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->data->meal_lock);
}

/*
** Handles the case of a single philosopher
** @philo: Pointer to the philosopher struct
**
** Locks the only available fork and prints the action.
** Waits slightly longer than time_to_die to simulate starvation.
** Unlocks the fork and ends the routine.
**
** Return: Always returns 0
*/
int	handle_single_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_philo_status(philo, "has taken a fork");
	precise_usleep(philo->data->time_to_die + 1, philo->data, philo);
	pthread_mutex_unlock(philo->left_fork);
	return (0);
}

/*
** Executes the philosopher's eating phase
** @philo: Pointer to the philosopher struct
**
** Attempts to take both forks using take_forks().
** If a death is detected before or during the phase, forks are released.
** If successful, prints "is eating", updates meal info, and sleeps.
** Releases the forks after eating.
*/
void	philo_eat(t_philo *philo)
{
	if (!take_forks(philo))
		return ;
	if (check_if_is_dead(philo->data))
	{
		release_forks(philo);
		return ;
	}
	update_meal_time(philo);
	print_philo_status(philo, "is eating");
	precise_usleep(philo->data->time_to_eat, philo->data, philo);
	release_forks(philo);
}

/*
** Simulates the sleep and think actions of a philosopher.
**
** Step-by-step:
** 1. Prints that the philosopher is sleeping.
** 2. Sleeps for time_to_sleep milliseconds using precise_usleep.
** 3. Prints that the philosopher is thinking.
** 4. If the number of philosophers is odd, waits 1 ms to avoid
**    synchronization issues.
**
** Why the extra 1 ms:
** With an odd number of philosophers (e.g., 5), there's always one
** philosopher out of sync. This small delay prevents all threads
** from re-aligning over time, which would increase fork collisions
** and possibly cause starvation.
*/
void	philo_sleep_and_think(t_philo *philo)
{
	print_philo_status(philo, "is sleeping");
	precise_usleep(philo->data->time_to_sleep, philo->data, philo);
	if (!check_if_is_dead(philo->data))
		print_philo_status(philo, "is thinking");
	if ((philo->data->num_philos % 2) == 1)
		precise_usleep(1, philo->data, philo);
}
