/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drobert- <drobert-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 14:09:00 by drobert-          #+#    #+#             */
/*   Updated: 2022/05/23 17:22:00 by drobert-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "philo.h"
#include <stdlib.h>

int     main(int argc, char **argv)
{
	t_data	*data;

	if (argc != 5 && argc != 6)
		return (1);
	data = data_init(argc, argv);
	printf("%s\n", *(argv + 1));
	printf("starttime: %lu\n", data->start_time);
	printf("num philos: %d\n", data->num_of_philos);
	printf("time to die: %d\n", data->time_to_die);
	printf("time to eat: %d\n", data->time_to_eat);
	printf("time to sleep: %d\n", data->time_to_sleep);
	printf("max eat: %d\n", data->max_eat);
	data_destroy(data);
}