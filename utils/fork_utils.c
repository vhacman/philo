/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 14:34:10 by vhacman           #+#    #+#             */
/*   Updated: 2025/06/28 20:32:27 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// I filosofi con ID dispari prendono prima la forchetta sinistra
// I filosofi con ID pari prendono prima la forchetta destra
// Questo evita il deadlock (tutti che aspettano tutti)
int	take_two_forks(t_philo *philo)
{
	int	is_even;
	int	is_odd;

	is_even = (philo->id % 2 == 0);
	is_odd = (philo->id % 2 == 1);
	if(is_odd)
	{
		pthread_mutex_lock(philo->left_fork);
		print_philo_status(philo, "has taken a fork");
		// Controllo se qualcuno è morto mentre aspettavo la prima forchetta
		if (check_death(philo->data))
		{
			pthread_mutex_unlock(philo->left_fork);
			return (0);
		}
		pthread_mutex_lock(philo->right_fork);
		print_philo_status(philo, "has taken a fork");
		// Controllo se qualcuno è morto mentre aspettavo la seconda forchetta
		if (check_death(philo->data))
		{
			pthread_mutex_unlock(philo->right_fork);
			pthread_mutex_unlock(philo->left_fork);
			return (0);
		}
	}
	else if (is_even)
	{
		pthread_mutex_lock(philo->right_fork);
		print_philo_status(philo, "has taken a fork");
		// Controllo se qualcuno è morto mentre aspettavo la prima forchetta
		if(check_death(philo->data))
		{
			pthread_mutex_unlock(philo->right_fork);
			return (0);
		}
		pthread_mutex_lock(philo->left_fork);
		print_philo_status(philo, "has taken a fork");
		// Controllo se qualcuno è morto mentre aspettavo la seconda forchetta
		if (check_death(philo->data))
		{
			pthread_mutex_unlock(philo->left_fork);
			pthread_mutex_unlock(philo->right_fork);
			return (0);
		}
	}
	return (1); //ho preso entrambe le forchette
}

int	take_forks(t_philo *philo)
{
	if(philo->data->num_philos == 1)
		return (handle_single_philo(philo));
	return (take_two_forks(philo));
}

void	release_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}
