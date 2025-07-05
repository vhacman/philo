/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 17:01:47 by vhacman           #+#    #+#             */
/*   Updated: 2025/07/05 15:55:47 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
** Initializes a philosopher before starting the routine.
**
** - Sets is_even if the philosopher ID is even.
** - Stores time_to_eat and time_to_die from simulation data.
** - Calculates time since last meal.
** - Calculates base_delay with calculate_initial_delay().
** - If even and safe, sleeps for half of time_to_eat to avoid sync.
*/
static void	init_philosopher_state(t_philo *philo, int	*is_even,
									int *base_delay)
{
	long	time_since_last_meal;
	long	time_to_die;
	long	time_to_eat;

	time_to_eat = philo->data->time_to_eat;
	time_to_die = philo->data->time_to_die;
	*is_even = (philo->id % 2 == 0);
	time_since_last_meal = get_time() - philo->last_meal_time;
	*base_delay = calculate_initial_delay(philo->data);
	if (*is_even && time_since_last_meal + time_to_eat
		< time_to_die)
		precise_usleep(time_to_eat / 2, philo->data, philo);
}

/*
** Adds a delay for even philosophers to reduce fork contention.
**
** 1. Returns immediately if base_delay is 0 or negative.
** 2. Calculates time left before the philosopher would die.
** 3. If safe, sleeps for base_delay using precise_usleep.
** Prevents death during delay by checking remaining time.
** Args:
** - philo: pointer to the philosopher
** - base_delay: delay to apply (in milliseconds)
*/
static void	apply_even_philo_delay(t_philo *philo, int base_delay)
{
	long	time_left;
	long	time_to_die;
	long	last_meal_time;

	last_meal_time = philo->last_meal_time;
	time_to_die = philo->data->time_to_die;
	if (base_delay <= 0)
		return ;
	time_left = time_to_die - (get_time() - last_meal_time);
	if (time_left > base_delay)
		precise_usleep(base_delay, philo->data, philo);
}

/*
** Executes one full cycle: optional delay, eat, check, sleep, think.
** 1. Applies delay if philosopher is even (to avoid fork collisions).
** 2. Exits early if someone has died.
** 3. Calls philo_eat and updates meal count.
** 4. Exits if someone died during eating.
** 5. Exits if the philosopher completed all meals.
** 6. Calls philo_sleep_and_think to sleep and print status.
** Args:
** - philo: pointer to philosopher struct
** - is_even: 1 if philosopher ID is even
** - base_delay: delay to apply for even philosophers
** Returns 1 to stop, 0 to continue.
*/
static int	execute_cycle(t_philo *philo, int is_even, int base_delay)
{
	if (is_even)
		apply_even_philo_delay(philo, base_delay);
	if (check_if_is_dead(philo->data))
		return (1);
	philo_eat(philo);
	if (check_if_is_dead(philo->data))
		return (1);
	if (has_completed_meals(philo->data, philo->id - 1))
		return (1);
	philo_sleep_and_think(philo);
	return (0);
}

/*
** Main function run by each philosopher thread.
** 1. Initializes philosopher state.
** 2. Applies a delay if the philosopher ID is even.
** 3. Loops until:
**    - A philosopher has died, or
**    - This philosopher has finished.
** 4. Calls execute_cycle in each loop.
** Returns NULL when the thread ends.
*/
void	*philo_routine(void *philo_arg)
{
	t_philo	*philo;
	int		is_even;
	int		base_delay;

	philo = (t_philo *)philo_arg;
	init_philosopher_state(philo, &is_even, &base_delay);
	while (!check_if_is_dead(philo->data))
	{
		if (execute_cycle(philo, is_even, base_delay))
			break ;
	}
	return (NULL);
}
