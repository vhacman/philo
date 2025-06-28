/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:58:01 by vhacman           #+#    #+#             */
/*   Updated: 2025/06/28 20:58:02 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//prepara i ''posti a tavola'' prima che i filosofi arrivino.
//decide quale forchetta ciascun filosofo puo' realmente usare.
int initialize_data(t_data *data)
{
	int i;

	i = 0;
	// continua fino all'ultimo filosofo
	while(i < data->num_philos)
	{
		data->philos[i].id = i + 1; // assegna ID: filosofo 0 ha ID = 1, filsofo 1 ha ID = 2'
		data->philos[i].meals_eaten = 0;     // All'inizio nessuno ha mangiato
		data->philos[i].last_meal_time = 0;  // All'inizio nessuno ha mai mangiato

	   // FORCHETTE - LA PARTE IMPORTANTE:
		data->philos[i].left_fork = &data->forks[i];  // Forchetta sinistra = forchetta con stesso numero del filosofo
	   // Forchetta destra = forchetta successiva
		data->philos[i].right_fork = &data->forks[(i + 1) % data->num_philos];
		// i + 1 = forchetta successiva
		// % data->num_philos = "se superi l'ultima forchetta, torna alla prima"
		// &data->forks[...] = indirizzo di quella forchetta

		data->philos[i].data = data;    // Ogni filosofo conosce i dati globali
		i++;                            // Passa al prossimo filosofo
	}
	return (0);
}

int init_simulation(t_data *data)
{
	if (init_mutexes(data) != 0)
		return (1);
	if (init_forks(data) != 0)
		return(cleanup_simulation_stage(data, 1));
	data->someone_died = 0;
	data->all_ate = 0;
	if (pthread_mutex_init(&data->status_lock, NULL) != 0)
		return (cleanup_simulation_stage(data, 1));
	data->philos = malloc(sizeof(t_philo) * data->num_philos);
	if(!data->philos)
		return(cleanup_simulation_stage(data, 2));
	initialize_data(data);
	return (0);
}
