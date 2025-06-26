/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:57:47 by vhacman           #+#    #+#             */
/*   Updated: 2025/06/26 16:07:44 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int ac, char **av)
{
    t_data  data;

    if (parse_args(ac, av, &data) != 0)
        return (1);
    if (init_simulation(&data))
    {
        cleanup_simulation(&data);
        return (1);
    }
    if (create_threads(&data) != 0)
    {
        cleanup_simulation(&data);
        return (1);
    }
}