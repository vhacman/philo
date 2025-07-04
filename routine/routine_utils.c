/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 11:45:32 by vhacman           #+#    #+#             */
/*   Updated: 2025/07/04 14:40:24 by vhacman          ###   ########.fr       */
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
void	update_meal_time(t_philo *philo)
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
	precise_usleep(philo->data->time_to_die + 1, philo->data);
	pthread_mutex_unlock(philo->left_fork);
	return (0);
}
