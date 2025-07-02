/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 14:04:46 by vhacman           #+#    #+#             */
/*   Updated: 2025/07/02 11:10:56 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
** Prints the philosopher's status with a timestamp and color
** @philo: Pointer to the philosopher struct
** @msg: Status message to print (e.g., "is eating", "died")
**
** Locks the print mutex to avoid concurrent output.
** Calculates timestamp relative to simulation start time.
** Chooses a color based on the message content.
** Prints the message only if no death has been detected,
** or if the message is "died".
** Unlocks the mutex after printing.
*/
void	print_philo_status(t_philo *philo, char *msg)
{
	long	timestamp;
	char	*color;

	pthread_mutex_lock(&philo->data->print_lock);
	timestamp = get_time() - philo->data->start_time;
	if (ft_strncmp(msg, "is eating", 9) == 0)
		color = COLOR_GREEN;
	else if (ft_strncmp(msg, "is sleeping", 11) == 0)
		color = COLOR_PURPLE;
	else if (ft_strncmp(msg, "is thinking", 11) == 0)
		color = COLOR_CYAN;
	else if (ft_strncmp(msg, "has taken a fork", 16) == 0)
		color = COLOR_ORANGE;
	else if (ft_strcmp(msg, "died") == 0)
		color = COLOR_RED;
	else
		color = COLOR_RESET;
	if (ft_strcmp(msg, "died") == 0 || !check_if_is_dead(philo->data))
	{
		printf("%ld %d ", timestamp, philo->id);
		printf("%s%s%s\n", color, msg, COLOR_RESET);
	}
	pthread_mutex_unlock(&philo->data->print_lock);
}
