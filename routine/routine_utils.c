/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 11:45:32 by vhacman           #+#    #+#             */
/*   Updated: 2025/06/28 20:47:04 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	update_meal_time(t_philo *philo)
{
// Prendo il "lucchetto" per aggiornare i dati del pasto in sicurezza
	pthread_mutex_lock(&philo->data->meal_lock);
// Aggiorno quando il filosofo ha mangiato per l'ultima volta (ADESSO)
	philo->last_meal_time = get_time();
// Incremento il contatore dei pasti consumati
	philo->meals_eaten++;
// Rilascio il "lucchetto"
	pthread_mutex_unlock(&philo->data->meal_lock);
}

int	handle_single_philo(t_philo *philo)
{
	//prendo unica forchetta disponibile
	pthread_mutex_lock(philo->left_fork);
	print_philo_status(philo, "has taken a fork");
	// Aspetto il tempo necessario per morire + 1 microsecondo
	// Non posso mangiare perché ho solo 1 forchetta (ne servono 2)
	// Quindi il filosofo morirà sicuramente di fame
	precise_usleep(philo->data->time_to_die + 1, philo->data);
	pthread_mutex_unlock(philo->left_fork);
	return (0);
}
