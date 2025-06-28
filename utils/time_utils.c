/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 14:03:39 by vhacman           #+#    #+#             */
/*   Updated: 2025/06/28 20:44:57 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time()
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}
/*
La normale funzione usleep() non è sempre precisa - a volte dorme un po' di più o di meno. Questa funzione invece:

È molto più precisa perché controlla continuamente il tempo
Non spreca risorse del computer perché usa comunque usleep() invece di girare a vuoto
Si adatta: dorme di più quando può, dorme poco quando deve essere preciso*/
void	precise_usleep(long m_seconds_to_wait, t_data *data)
{
	long	start_time;
	long	time_passed;

	start_time = get_time();
	while (1)
	{
		// se la simulazione è finita (morte o tutti hanno mangiato), esco subito
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

