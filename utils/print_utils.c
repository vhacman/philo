/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 14:04:46 by vhacman           #+#    #+#             */
/*   Updated: 2025/06/28 19:41:55 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_philo_status(t_philo *philo, char *msg)
{
	long	timestamp;
	char	*color;

	// Prendo il "lucchetto" per stampare (solo uno alla volta può stampare)
	pthread_mutex_lock(&philo->data->print_lock);
	// Calcolo quanto tempo è passato dall'inizio della simulazione
	timestamp = get_time() - philo->data->start_time;
	// Scelgo il colore in base all'azione del filosofo
	if (ft_strncmp(msg, "is eating", 9) == 0)
		color = COLOR_GREEN;      // Verde per mangiare
	else if (ft_strncmp(msg, "is sleeping", 11) == 0)
		color = COLOR_PURPLE;     // Viola per dormire
	else if (ft_strncmp(msg, "is thinking", 11) == 0)
		color = COLOR_CYAN;       // Ciano per pensare
	else if (ft_strncmp(msg, "has taken a fork", 16) == 0)
		color = COLOR_ORANGE;     // Arancione per prendere forchetta
	else if (ft_strcmp(msg, "died") == 0)
		color = COLOR_RED;        // Rosso per morte
	else
		color = COLOR_RESET;      // Nessun colore per altro
	// Stampo SOLO se:
	// - È un messaggio di morte (sempre importante mostrarlo)
	// - OPPURE nessuno è ancora morto (se qualcuno è morto, smetto di stampare)
	if (ft_strcmp(msg, "died") == 0 || !check_death(philo->data))
	{
		printf("%ld %d ", timestamp, philo->id);        // Tempo e ID filosofo
		printf("%s%s%s\n", color, msg, COLOR_RESET);    // Messaggio colorato
	}
	// Rilascio il "lucchetto" per permettere ad altri di stampare
	pthread_mutex_unlock(&philo->data->print_lock);
}

