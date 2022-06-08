/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drobert- <drobert-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 16:21:31 by drobert-          #+#    #+#             */
/*   Updated: 2022/06/08 14:19:42 by drobert-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <stdlib.h>
#include "philo.h"
#include <stdio.h>

int	destroy_mutexes(pthread_mutex_t *forks, int i)
{
	while (--i >= 0)
		pthread_mutex_destroy(forks + i);
	return (1);
}

void	free_vars(t_collections *c, t_data *data)
{
	free(c->philos);
	free(c->philosophers);
	free(c->forks);
	free(c->vars);
	data_destroy(data);
}

void	sleep_until(t_ulong time, t_vars *v)
{
	while (get_time() < time)
	{
		pthread_mutex_lock(&v->data->m_death);
		if (v->data->has_died)
		{
			pthread_mutex_unlock(&v->data->m_death);
			break ;
		}
		pthread_mutex_unlock(&v->data->m_death);
		if (get_time() - v->philo->time_last_eat > v->data->time_to_die)
		{
			action_die(v);
			return ;
		}
	}
}

void	print_status(t_vars *vars, char *str)
{
	pthread_mutex_lock(&vars->data->m_death);
	if (!vars->data->has_died)
		printf("%lu\t\t%d\t %s\n",
			get_time() - vars->philo->start_time, vars->philo->id, str);
	pthread_mutex_unlock(&vars->data->m_death);
}

t_ulong	get_time(void)
{
	struct timeval	tval;

	if (gettimeofday(&tval, 0) < 0)
		return (0);
	return ((tval.tv_sec * 1000) + (tval.tv_usec / 1000));
}
