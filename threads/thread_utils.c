/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 14:15:19 by vhacman           #+#    #+#             */
/*   Updated: 2025/06/26 16:15:02 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int create_threads(t_data *data)
{
    int i;

    data->start_time = get_time();
    i = 0;
    while(i < data->num_philos)
    {
        //tutti iniziano ''appena mangiato''
        data->philos[i].last_meal_time = data->start_time;
        if (pthread_create(&data->philos[i].thread, NULL, philo_routine, &data->philos[i]) != 0)
        {
            printf("Error: thread creation failed\n");
            return (1);
        }
        i++;
    }
    return (0);
}

//aspetta che i thread terminano.
int join_threads(t_data *data)
{
    int i;

    i = 0;
    while(i < data->num_philos)
    {
        pthread_join(data->philos[i].thread, NULL);
        i++;
    }
    return (0);
}
