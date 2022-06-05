/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drobert- <drobert-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 16:18:12 by drobert-          #+#    #+#             */
/*   Updated: 2022/06/05 15:57:56 by drobert-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>

static int	ft_atoi(const char *str)
{
	long	num;

	num = 0;
	while (*str >= '0' && *str <= '9')
		num = (num * 10) + (*str++ - '0');
	return (num);
}

static int	is_valid(int argc, char **argv)
{
	int	i;

	while (--argc)
	{
		i = -1;
		while (argv[argc][++i])
			if (argv[argc][i] < '0' || argv[argc][i] > '9')
				return (0);
	}
	return (1);
}

static void	set_vars(int argc, char **argv, t_data *data)
{
	data->has_died = 0;
	data->full_amount = 0;
	data->num_of_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->max_eat = ft_atoi(argv[5]);
	else
		data->max_eat = -1;
}

t_data	*data_init(int argc, char **argv)
{
	t_data	*data;

	if (!is_valid(argc, argv))
		return (0);
	data = malloc(sizeof(t_data));
	if (!data)
		return (0);
	if (pthread_mutex_init(&data->m_death, 0))
		return (data_destroy(data));
	if (pthread_mutex_init(&data->m_fullamount, 0))
	{
		pthread_mutex_destroy(&data->m_death);
		return (data_destroy(data));
	}
	set_vars(argc, argv, data);
	if (!data->time_to_die || !data->num_of_philos)
	{
		pthread_mutex_destroy(&data->m_death);
		pthread_mutex_destroy(&data->m_fullamount);
		free(data);
		return (0);
	}
	return (data);
}

void	*data_destroy(t_data *d)
{
	free(d);
	return (0);
}
