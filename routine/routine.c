/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 17:01:47 by vhacman           #+#    #+#             */
/*   Updated: 2025/07/03 10:50:47 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
** Calculates a safe base_delay delay for even-numbered philosophers
** to wait before starting their routine. This helps to reduce
** contention when picking up forks at the beginning.
**
** Step-by-step:
** 1. Computes max_safe_delay as: time_to_die - time_to_eat - time_to_sleep.
**    This ensures the delay does not risk philosopher death.
** 2. Sets initial base_delay to half of time_to_eat for staggering.
** 3. If max_safe_delay is non-positive, sets base_delay to 0 (no delay allowed).
** 4. If base_delay is greater than max_safe_delay, it is
**     capped to max_safe_delay.
**
** This delay is applied only to even philosophers at the start.
**
** Arguments:
** - data: pointer to main simulation data
**
** Returns the computed base_delay in milliseconds.
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
** Main routine executed by each philosopher thread. Simulates the
** philosopher's behavior: eating, sleeping, and thinking, while checking
** for death or completion conditions.
**
** Step-by-step:
** 1. Casts the argument to a t_philo pointer.
** 2. Checks if the philosopher's ID is even.
** 3. Uses calculate_initial_delay to get a safe base_delay to stagger
**    even philosophers. If delay > 0, applies it once at the start.
** 4. Enters a loop that continues while no death is detected.
** 5. If even, applies base_delay again before eating (extra staggering).
** 6. philo_eat: Picks up forks, eats, and updates meal counters.
**    If someone died, exits early.
** 7. has_completed_meals: Checks if this philosopher met meal quota.
**    If so, exits the loop.
** 8. philo_sleep_and_think: Simulates sleeping and thinking actions.
** 9. If someone dies during sleep or think, exits the loop.
**
** Arguments:
** - philo_arg: void pointer to a t_philo struct
**
** Returns NULL when the thread finishes execution.
*/
void	*philo_routine(void *philo_arg)
{
	t_philo	*philo;
	int		is_even;
	long	base_delay;

	philo = (t_philo *)philo_arg;
	is_even = (philo->id % 2 == 0);
	base_delay = calculate_initial_delay(philo->data);
	if (is_even && base_delay > 0)
		precise_usleep(base_delay, philo->data);
	while (!check_if_is_dead(philo->data))
	{
		if (is_even && base_delay > 0)
			precise_usleep(base_delay, philo->data);
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
