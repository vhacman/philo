/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 17:01:47 by vhacman           #+#    #+#             */
/*   Updated: 2025/07/04 15:07:18 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
** Calculates how long even-numbered philosophers should wait before
** trying to eat. This delay helps avoid deadlocks and reduces fork
** contention at the start of the simulation.
**
** How it works:
** 1. Calculates the maximum safe delay based on:
**    time_to_die - time_to_eat - time_to_sleep
** 2. Uses half of time_to_eat as the base delay.
** 3. If the safe delay is too small (≤ 0), sets base delay to 0.
** 4. If base delay is too large, caps it to the safe limit.
**
** Arguments:
** - data: pointer to the simulation data structure
**
** Returns a safe delay in milliseconds.
*/
long	calculate_initial_delay(t_data *data)
{
	long	base_delay;
	long	max_safe_delay;

	max_safe_delay = data->time_to_die - data->time_to_eat
		- data->time_to_sleep;
	base_delay = data->time_to_eat / 2;
	if (max_safe_delay <= 0)
		base_delay = 0;
	else if (base_delay > max_safe_delay)
		base_delay = max_safe_delay;
	return (base_delay);
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
	precise_usleep(philo->data->time_to_eat, philo->data);
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
	precise_usleep(philo->data->time_to_sleep, philo->data);
	print_philo_status(philo, "is thinking");
	if ((philo->data->num_philos % 2) == 1)
		precise_usleep(1, philo->data);
}

/*
** Main function for each philosopher thread. It controls the behavior
** of a philosopher: eating, sleeping, thinking, and checking if they
** should stop.
**
** How it works:
** 1. Converts the argument to a philosopher pointer.
** 2. Checks if the philosopher ID is even.
** 3. Even philosophers wait a short time before starting, to avoid
**    taking forks at the same time as the others.
** 4. Enters a loop that runs until:
**    - the simulation ends due to death, or
**    - the philosopher has eaten enough times.
** 5. In each loop:
**    - Even philosophers may wait again to reduce collisions.
**    - If someone died, exit.
**    - Eat using philo_eat().
**    - If someone died while eating, exit.
**    - If this philosopher finished all meals, exit.
**    - Sleep and think using philo_sleep_and_think().
**    - If someone died during sleep, exit.
**
** Arguments:
** - philo_arg: pointer to a philosopher structure (void*)
**
** Returns NULL when the philosopher is done.
*/
void	*philo_routine(void *philo_arg)
{
	t_philo	*philo;
	int		is_even;
	int		base_delay;

	philo = (t_philo *)philo_arg;
	is_even = (philo->id % 2 == 0);
	base_delay = calculate_initial_delay(philo->data);
	if (is_even)
		precise_usleep(philo->data->time_to_eat / 2, philo->data);
	while (!check_if_is_dead(philo->data))
	{
		if (is_even && base_delay > 0)
			precise_usleep(base_delay, philo->data);
		if (check_if_is_dead(philo->data))
			break ;
		philo_eat(philo);
		if (check_if_is_dead(philo->data))
			break ;
		if (has_completed_meals(philo->data, philo->id - 1))
			break ;
		philo_sleep_and_think(philo);
		if (check_if_is_dead(philo->data))
			break ;
	}
	return (NULL);
}
