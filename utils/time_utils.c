/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 14:03:39 by vhacman           #+#    #+#             */
/*   Updated: 2025/07/05 18:32:58 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
** Computes a safe delay for even-numbered philosophers to reduce
** fork contention at the start of the simulation.
**
** Step-by-step:
** 1. Calculates the maximum safe delay:
**    time_to_die - time_to_eat - time_to_sleep.
** 2. Sets the base delay as half of time_to_eat.
** 3. If the safe delay is zero or negative, sets delay to 0.
** 4. If the base delay is too large, turns it to the safe limit.
** - Delay in milliseconds that avoids philosopher death.
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
** Returns the current time in milliseconds
**
** Uses gettimeofday() to retrieve the current time.
** Converts the result from seconds and microseconds to milliseconds.
** Return: Current time in milliseconds as a long integer
*/
long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

/*
** Adjusts the sleep time to avoid philosopher death during sleep.
** - If 'philo' is NULL, does nothing.
** - Calculates how much time is left before the philosopher dies
**   based on time_to_die and last_meal_time.
** - If there’s no time left, exits immediately.
** - If the requested sleep time is too long, reduces it to avoid
**   sleeping past the death limit.
**
** Args:
** - wait_time: pointer to the sleep duration (in ms)
** - data: pointer to simulation data
** - philo: pointer to the current philosopher
*/
static void	limit_sleep_time(long *wait_time, t_data *data,
								t_philo *philo)
{
	long	time_to_die;
	long	start_time;

	if (philo == NULL)
		return ;
	start_time = get_time();
	time_to_die = data->time_to_die
		- (start_time - philo->last_meal_time);
	if (time_to_die <= 0)
		return ;
	if (*wait_time > time_to_die)
		*wait_time = time_to_die;
}

/*
** Sleeps for an accurate duration, with safety checks to avoid death.
**
** 1. Gets the current time as start_time.
** 2. Calls limit_sleep_time to adjust wait_time if needed.
** 3. Enters a loop:
**    - Exits immediately if a philosopher has died.
**    - Calculates elapsed time since start.
**    - If elapsed >= wait_time, exits the loop.
**    - Otherwise, computes remaining time and sleeps:
**        • If > 20 ms left, sleeps for (remaining - 10) ms.
**        • If > 5 ms left, sleeps for 1 ms.
**        • Else, sleeps for 100 µs.
**
** Ensures the philosopher wakes up as close as possible to wait_time
** without sleeping too long and risking death.
*/
void	precise_usleep(long wait_time, t_data *data, t_philo *philo)
{
	long	start_time;
	long	current_time;
	long	elapsed;
	long	remaining;

	start_time = get_time();
	limit_sleep_time(&wait_time, data, philo);
	while (1)
	{
		if (check_if_is_dead(data))
			return ;
		current_time = get_time();
		elapsed = current_time - start_time;
		if (elapsed >= wait_time)
			break ;
		remaining = wait_time - elapsed;
		if (remaining > 20)
			usleep((remaining - 10) * 1000);
		else if (remaining > 5)
			usleep(1000);
		else
			usleep(100);
	}
}
