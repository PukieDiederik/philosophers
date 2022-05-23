/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drobert- <drobert-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 14:09:00 by drobert-          #+#    #+#             */
/*   Updated: 2022/05/23 16:51:00 by drobert-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "philo.h"
#include <stdlib.h>

int main(int argc, char **argv)
{
	t_data	*data;

	if (argc != 5 && argc != 6)
		return (1);
	data = data_init(argc, argv);
	printf("%lu", data->start_time);
	data_destroy(data);
}