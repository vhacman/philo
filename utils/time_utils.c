/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 14:03:39 by vhacman           #+#    #+#             */
/*   Updated: 2025/07/04 15:21:49 by vhacman          ###   ########.fr       */
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
** Sleeps for an exact number of milliseconds while periodically checking
** if the simulation has ended due to a philosopher's death.
**
** Step-by-step:
** 1. Stores the start timestamp using get_time().
** 2. Enters a loop that continues until the desired delay is reached.
** 3. On each iteration:
**    - Checks if a philosopher has died (check_if_is_dead). If so, exits.
**    - Computes the elapsed time since start.
**    - If the target time is reached or exceeded, breaks the loop.
**    - Otherwise, calculates the remaining time and adapts the sleep:
**        - If remaining > 20 ms: sleeps for (remaining - 10) ms.
**        - If remaining > 5 ms: sleeps for 1 ms.
**        - Else: sleeps for 100 µs (ultra short final delay).
**
** This avoids oversleeping and ensures accurate timing without busy wait.
** Returns nothing. Exits early if death is detected.
*/

void	precise_usleep(long m_seconds_to_wait, t_data *data)
{
	long	start_time;
	long	current_time;
	long	elapsed;
	long	remaining;

	start_time = get_time();
	
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
