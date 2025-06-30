/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 14:03:39 by vhacman           #+#    #+#             */
/*   Updated: 2025/06/30 12:32:55 by vhacman          ###   ########.fr       */
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
** Sleeps for a precise number of milliseconds
** @m_seconds_to_wait: Time to wait in milliseconds
** @data: Pointer to the simulation data structure
**
** Waits in a loop until the specified time has passed.
** Checks the death flag to exit early if a philosopher has died.
** Uses shorter sleep intervals to improve timing precision and responsiveness.
*/
void	precise_usleep(long m_seconds_to_wait, t_data *data)
{
	long	start_time;
	long	time_passed;

	start_time = get_time();
	while (1)
	{
		if (check_death(data))
			return ;
		time_passed = get_time() - start_time;
		if (time_passed >= m_seconds_to_wait)
			break ;
		if (m_seconds_to_wait - time_passed > 10)
			usleep((m_seconds_to_wait - time_passed) * 500);
		else
			usleep(100);
	}
}
