/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drobert- <drobert-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 16:18:12 by drobert-          #+#    #+#             */
/*   Updated: 2022/05/23 17:02:56 by drobert-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>

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

	if (!is_valid(argc, argv))
		return (0);
	data = malloc(sizeof(t_data));
	if (!data)
		return (0);
	data->start_time = get_time();
	return (data);
};

void	data_destroy(t_data *d)
{
	free(d);
}