/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 17:01:47 by vhacman           #+#    #+#             */
/*   Updated: 2025/06/28 20:47:17 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
void	philo_eat(t_philo *philo)
{
	if (!take_forks(philo))
		return ;
	if (check_death(philo->data))
	{
		release_forks(philo);
		return ;
	}
	print_philo_status(philo, "is eating");
	update_meal_time(philo);
	precise_usleep(philo->data->time_to_eat, philo->data);
	release_forks(philo);
}

void	philo_sleep_and_think(t_philo *philo)
{
	print_philo_status(philo, "is sleeping");
	precise_usleep(philo->data->time_to_sleep, philo->data);
	print_philo_status(philo, "is thinking");
}
void	*philo_routine(void *philo_arg)
{
	t_philo	*philo;
	int		is_even;
	int		meals_done;

	philo = (t_philo *)philo_arg;
	is_even = (philo->id % 2 == 0);
	if (is_even)
		precise_usleep(philo->data->time_to_eat / 2, philo->data);
	while(!check_death(philo->data))
	{
		philo_eat(philo);
		if(check_death(philo->data))
			break;
		pthread_mutex_lock(&philo->data->meal_lock);
		meals_done = (philo->data->meals_required  > 0 && philo->meals_eaten >= philo->data->meals_required);
		pthread_mutex_unlock(&philo->data->meal_lock);
		if (meals_done)
			break;
		philo_sleep_and_think(philo);
	}
	return (NULL);
}

