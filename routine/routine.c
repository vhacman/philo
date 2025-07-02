/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 17:01:47 by vhacman           #+#    #+#             */
/*   Updated: 2025/07/02 14:24:39 by vhacman          ###   ########.fr       */
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
	if (check_if_is_dead(philo->data))
	{
		release_forks(philo);
		return ;
	}
	update_meal_time(philo);
	print_philo_status(philo, "is eating");
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
** Main routine executed by each philosopher thread. It simulates the
** philosopher's behavior: eating, sleeping, and thinking, while checking
** for termination conditions.
**
** Step-by-step:
** 1. Casts the argument to a t_philo pointer.
** 2. If the philosopher ID is even, waits for half eat time to reduce
**    contention on fork mutexes (staggered start).
** 3. Enters a loop that runs until the simulation ends (death detected).
** 4. philo_eat: Tries to pick up forks, eats, and updates meal counters.
**    If the simulation ends during this phase, it exits early.
** 5. Locks the meal_lock to check if the required number of meals
**    has been reached. If yes, exits the loop.
** 6. philo_sleep_and_think: Sleeps for time_to_sleep, then "thinks".
** 7. If the simulation ends during sleep/thinking, exits early.
**
** Arguments:
** - philo_arg: void pointer to a t_philo struct
**
** Returns NULL when the thread ends execution.
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
	while (!check_if_is_dead(philo->data))
	{
		philo_eat(philo);
		if (check_if_is_dead(philo->data))
			break ;
		pthread_mutex_lock(&philo->data->meal_lock);
		meals_done = (philo->data->meals_required > 0
				&& philo->meals_eaten >= philo->data->meals_required);
		pthread_mutex_unlock(&philo->data->meal_lock);
		if (meals_done)
			break ;
		philo_sleep_and_think(philo);
		if (check_if_is_dead(philo->data))
			break ;
	}
	return (NULL);
}
