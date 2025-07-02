/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 14:34:10 by vhacman           #+#    #+#             */
/*   Updated: 2025/07/02 14:54:58 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
** Philosopher with odd ID takes left fork first, then right
** @philo: Pointer to the philosopher struct
**
** Locks left fork and prints the action.
** If a death is detected, releases the fork acheckif_is_deadnd returns 0.
** Then locks right fork and prints the action.
** If a death is detected, releases both forks and returns 0.
**
** Return: 1 if both forks were successfully taken, 0 otherwise
*/
int	take_two_forks_odd(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_philo_status(philo, "has taken a fork");
	if (check_if_is_dead(philo->data))
	{
		pthread_mutex_unlock(philo->left_fork);
		return (0);
	}
	pthread_mutex_lock(philo->right_fork);
	print_philo_status(philo, "has taken a fork");
	if (check_if_is_dead(philo->data))
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		return (0);
	}
	return (1);
}

/*
** Philosopher with even ID takes right fork first, then left
** @philo: Pointer to the philosopher struct
**
** Locks right fork and prints the action.
** If a death is detected, releases the fork and returns 0.
** Then locks left fork and prints the action.
** If a death is detected, releases both forks and returns 0.
**
** Return: 1 if both forks were successfully taken, 0 otherwise
*/
int	take_two_forks_even(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	print_philo_status(philo, "has taken a fork");
	if (check_if_is_dead(philo->data))
	{
		pthread_mutex_unlock(philo->right_fork);
		return (0);
	}
	pthread_mutex_lock(philo->left_fork);
	print_philo_status(philo, "has taken a fork");
	if (check_if_is_dead(philo->data))
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return (0);
	}
	return (1);
}

/*
** Chooses fork acquisition order based on philosopher ID
** @philo: Pointer to the philosopher struct
**
** Odd IDs call take_two_forks_odd, even IDs call take_two_forks_even.
**
** Return: 1 if both forks were taken, 0 otherwise
*/
int	take_two_forks(t_philo *philo)
{
	if (philo->id % 2 == 1)
		return (take_two_forks_odd(philo));
	else
		return (take_two_forks_even(philo));
}

/*
** Handles fork acquisition for philosophers
** @philo: Pointer to the philosopher struct
**
** Special case: if only one philosopher exists, calls handler and returns.
** Otherwise, attempts to take two forks using take_two_forks().
**
** Return: 1 if forks were successfully taken, 0 otherwise
*/
int	take_forks(t_philo *philo)
{
	if (philo->data->num_philos == 1)
		return (handle_single_philo(philo));
	return (take_two_forks(philo));
}

/*
** Releases both forks held by the philosopher
** @philo: Pointer to the philosopher struct
**
** Unlocks the right and left fork mutexes, in that order.
*/
void	release_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}
