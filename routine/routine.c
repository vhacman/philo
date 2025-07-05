/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 17:01:47 by vhacman           #+#    #+#             */
/*   Updated: 2025/07/05 15:06:39 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
** Initializes the state of a philosopher before starting the routine.
** It checks if the philosopher is even, calculates a base delay, and
** applies a small initial wait if it's safe to do so.
**
**  Stores time_to_eat and time_to_die from simulation data.
**  Calculates how long it's been since the last meal.
**  Calculates base_delay using calculate_initial_delay().
**  If the philosopher is even, and there's enough time before death,
**  sleeps for half of time_to_eat to avoid all philosophers acting
**  at the same time.
**
** Arguments:
** - philo: pointer to the philosopher structure
** - is_even: output flag, 1 if the philosopher ID is even
** - base_delay: output value, used to delay eating during the cycle
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
** Adds a small delay for even philosophers before they eat.
** This helps reduce fork contention by spacing out thread actions.
**
** 1. If base_delay is 0 or negative, returns immediately.
** 2. Calculates how much time is left before the philosopher dies.
** 3. If there is enough time left, sleeps for base_delay milliseconds
**    using precise_usleep.
** This avoids situations where a philosopher would die during the delay.
**
** Arguments:
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
** Executes one full cycle for a philosopher: wait (if even),
** eat, check if finished, sleep and think.
**
** 1. If the philosopher is even, applies a delay to avoid
**    collisions with other threads (fork contention).
** 2. If someone has died, exits early.
** 3. philo_eat: tries to eat and updates meals.
** 4. If someone died during eating, exits.
** 5. Checks if the philosopher has completed all meals.
**    If yes, exits.
** 6. philo_sleep_and_think: sleeps and prints status.
**
** Arguments:
** - philo: pointer to the philosopher structure
** - is_even: 1 if the philosopher ID is even
** - base_delay: delay to apply if philosopher is even
** Returns 1 if the philosopher must stop, 0 to continue looping.
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
** Main routine run by each philosopher thread.
** Controls the philosopher's behavior during the simulation.
** 1. Converts the argument to a t_philo pointer.
** 2. Calls init_philosopher_state to:
**    - Check if the philosopher is even
**    - Calculate the delay to apply before eating
** 3. Enters a loop that continues until:
**    - A philosopher dies (check_if_is_dead)
**    - Or the current philosopher finishes (via execute_cycle)
** 4. In each loop, execute_cycle performs one full cycle.
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
