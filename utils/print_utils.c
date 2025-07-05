/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 14:04:46 by vhacman           #+#    #+#             */
/*   Updated: 2025/07/05 18:58:56 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
** Prints the philosopher's status with a timestamp and color
** Locks the print mutex to avoid concurrent output.
** Calculates timestamp relative to simulation start time.
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
		printf(COLOR_YELLOW "%ld " COLOR_RESET, timestamp);
		printf(COLOR_BLUE "%d " COLOR_RESET, philo->id);
		printf("%s%s%s\n", color, msg, COLOR_RESET);
	}
	pthread_mutex_unlock(&philo->data->print_lock);
}

void	print_usage_error(void)
{
	printf(COLOR_RED "Error: wrong number of arguments" COLOR_RESET "\n");
	printf(COLOR_GREEN "Example: ./philo num  die  eat  sleep"
		COLOR_RESET "\n");
	printf(COLOR_GREEN "         ./philo  4   310  200  100"
		COLOR_RESET "\n");
}

void	print_numeric_error(void)
{
	printf(COLOR_RED "Error: arguments must be numeric"
		COLOR_RESET "\n");
	printf(COLOR_GREEN "Example: ./philo num  die eat sleep"
		COLOR_RESET "\n");
	printf(COLOR_GREEN "         ./philo  5   800 200 200"
		COLOR_RESET "\n");
}
