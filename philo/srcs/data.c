/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drobert- <drobert-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 16:18:12 by drobert-          #+#    #+#             */
/*   Updated: 2022/05/23 16:55:51 by drobert-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

static int is_valid(int argc, char **argv)
{
	while (--argc)
	{
		while (*argv[argc])
			if (!ft_isdigit(*argv[argc]++))
				return (0);
	}
	return (1);
}

t_data *data_init(int argc, char **argv)
{
	t_data	*data;
	struct timeval tval;

	if (!is_valid(argc, argv))
		return (0);
	data = malloc(sizeof(t_data));
	if (!data)
		return (0);
	gettimeofday(&tval,0);
	data->start_time = (tval.tv_sec * 1000) + (tval.tv_usec / 1000);
	return (data);
};

void	data_destroy(t_data *d)
{
	free(d);
}