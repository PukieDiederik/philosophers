/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drobert- <drobert-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 14:09:00 by drobert-          #+#    #+#             */
/*   Updated: 2022/05/23 17:29:26 by drobert-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include "philo.h"

int     main(int argc, char **argv)
{
	t_data	*data;
	pthread_mutex_t *forks;
	int i = 0;

	if (argc != 5 && argc != 6)
		return (1);
	data = data_init(argc, argv);
	forks = malloc(sizeof(pthread_mutex_t) * data->num_of_philos);
	while (i < data->num_of_philos)
		pthread_mutex_init(forks + i, 0);
	while(i < data->num_of_philos)
		pthread_mutex_destroy(forks + i);

	printf("%s\n", *(argv + 1));
	printf("starttime: %lu\n", data->start_time);
	printf("num philos: %d\n", data->num_of_philos);
	printf("time to die: %d\n", data->time_to_die);
	printf("time to eat: %d\n", data->time_to_eat);
	printf("time to sleep: %d\n", data->time_to_sleep);
	printf("max eat: %d\n", data->max_eat);
	data_destroy(data);
}