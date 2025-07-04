/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 14:03:39 by vhacman           #+#    #+#             */
/*   Updated: 2025/07/04 18:32:56 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
** Returns the current time in milliseconds
**
** Uses gettimeofday() to retrieve the current time.
** Converts the result from seconds and microseconds to milliseconds.
**
** Return: Current time in milliseconds as a long integer
*/
long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

/*
** Limits the sleep time so that the philosopher doesn't die
** while sleeping too long.
**
** How it works:
** - If 'philo' is given (not NULL), it checks how much time is
**   left before that philosopher would die.
** - If the philosopher has no time left, it returns immediately.
** - If the sleep time is longer than the time left to live,
**   it reduces the sleep time to match the safe limit.
**
** This is useful to avoid situations where a philosopher
** dies during a long sleep.
**
** Arguments:
** - m_seconds_to_wait: pointer to the time to sleep (in ms)
** - data: simulation state (contains time_to_die)
** - philo: the philosopher (can be NULL)
*/
static void	precise_usleep_utils(long *m_seconds_to_wait, t_data *data,
								t_philo *philo)
{
	long	time_to_die;
	long	start_time;

	if (philo != NULL)
	{
		start_time = get_time();
		time_to_die = data->time_to_die
			- (start_time - philo->last_meal_time);
		if (time_to_die <= 0)
			return ;
		if (*m_seconds_to_wait > time_to_die)
			*m_seconds_to_wait = time_to_die;
	}
}

/*
** Sleeps for a specific amount of time in milliseconds, but in a safe way:
** it checks regularly if someone died, and avoids sleeping too long
** if the philosopher is close to dying.
**
** How it works:
** 1. Gets the current time at the start.
** 2. Calls precise_usleep_utils to reduce the sleep time if the
**    philosopher could die soon.
** 3. Enters a loop:
**    - If someone died, exits immediately.
**    - Checks how much time has passed since the start.
**    - If enough time passed, stops sleeping.
**    - Otherwise, waits a short time based on how much is left:
**        > 20ms → sleep (remaining - 10) ms
**        > 5ms  → sleep 1 ms
**        ≤ 5ms  → sleep 100 µs
**
** This gives a very accurate sleep without blocking the program,
** and avoids killing philosophers during long waits.
**
** Arguments:
** - m_seconds_to_wait: how long to sleep (in ms)
** - data: simulation state (used to check if someone died)
** - philo: current philosopher (used to calculate safe delay)
*/
void	precise_usleep(long m_seconds_to_wait, t_data *data, t_philo *philo)
{
	long	start_time;
	long	current_time;
	long	elapsed;
	long	remaining;

	start_time = get_time();
	precise_usleep_utils(&m_seconds_to_wait, data, philo);
	while (1)
	{
		if (check_if_is_dead(data))
			return ;
		current_time = get_time();
		elapsed = current_time - start_time;
		if (elapsed >= m_seconds_to_wait)
			break ;
		remaining = m_seconds_to_wait - elapsed;
		if (remaining > 20)
			usleep((remaining - 10) * 1000);
		else if (remaining > 5)
			usleep(1000);
		else
			usleep(100);
	}
}
