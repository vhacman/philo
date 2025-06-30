/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 17:01:47 by vhacman           #+#    #+#             */
/*   Updated: 2025/06/30 12:35:49 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	if (check_death(philo->data))
	{
		release_forks(philo);
		return ;
	}
	print_philo_status(philo, "is eating");
	update_meal_time(philo);
	precise_usleep(philo->data->time_to_eat, philo->data);
	release_forks(philo);
}

/*
** Executes sleeping and thinking phases
** @philo: Pointer to the philosopher struct
**
** Prints "is sleeping" and waits for time_to_sleep.
** Then prints "is thinking" to indicate the next phase.
*/
void	philo_sleep_and_think(t_philo *philo)
{
	print_philo_status(philo, "is sleeping");
	precise_usleep(philo->data->time_to_sleep, philo->data);
	print_philo_status(philo, "is thinking");
}

/*
** Main routine executed by each philosopher thread
** @philo_arg: Pointer to the philosopher struct (cast from void*)
**
** If the philosopher ID is even, delays slightly to stagger fork access.
** Enters a loop that runs while no one has died:
** - Eats (philo_eat)
** - Checks if the philosopher has finished required meals
** - Sleeps and thinks (philo_sleep_and_think)
** The routine exits on death or when enough meals have been eaten.
**
** Return: NULL (used as pthread thread function)
*/
void	*philo_routine(void *philo_arg)
{
	t_philo	*philo;
	int		is_even;
	int		meals_done;

	philo = (t_philo *)philo_arg;
	is_even = (philo->id % 2 == 0);
	if (is_even)
		precise_usleep(philo->data->time_to_eat / 2, philo->data);
	while (!check_death(philo->data))
	{
		philo_eat(philo);
		if (check_death(philo->data))
			break ;
		pthread_mutex_lock(&philo->data->meal_lock);
		meals_done = (philo->data->meals_required > 0
				&& philo->meals_eaten >= philo->data->meals_required);
		pthread_mutex_unlock(&philo->data->meal_lock);
		if (meals_done)
			break ;
		philo_sleep_and_think(philo);
	}
	return (NULL);
}
