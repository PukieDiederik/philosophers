/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drobert- <drobert-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 16:21:31 by drobert-          #+#    #+#             */
/*   Updated: 2022/05/31 14:18:42 by drobert-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <stdlib.h>
#include "philo.h"
#include <stdio.h>

void sleep_until(ULONG time, t_vars *v)
{
	while (get_time() < time && !v->data->has_died)
		if(get_time() - v->philo->time_last_eat > (ULONG) v->data->time_to_die)
		{
			action_die(v);
			return ;
		}
}

void print_status(t_vars *vars, char *str)
{
	pthread_mutex_lock(&vars->data->m_death);
	printf("%lu\t\t%d\t %s\n",
		   get_time() - vars->philo->start_time, vars->philo->id, str);
	pthread_mutex_unlock(&vars->data->m_death);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	long	num;

	num = 0;
	while (*str >= '0' && *str <= '9')
		num = (num * 10) + (*str++ - '0');
	return (num);
}

ULONG get_time(void)
{
	struct	timeval	tval;

	if (gettimeofday(&tval,0) < 0)
		return (0);
	return ((tval.tv_sec * 1000) + (tval.tv_usec / 1000));
}