/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drobert- <drobert-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 13:20:54 by drobert-          #+#    #+#             */
/*   Updated: 2022/06/03 11:44:26 by drobert-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <pthread.h>

void	action_think(t_vars *vars, t_ulong time)
{
	print_status(vars, "is thinking");
	sleep_until(get_time() + time, vars);
	pthread_mutex_lock(&vars->data->m_fullamount);
	if (vars->data->has_died
		|| vars->data->full_amount == vars->data->num_of_philos)
	{
		pthread_mutex_unlock(&vars->data->m_fullamount);
		return ;
	}
	pthread_mutex_unlock(&vars->data->m_fullamount);
	action_eat(vars);
}

void	action_eat(t_vars *vars)
{
	pthread_mutex_lock(vars->philo->l_fork);
	print_status(vars, "has taken their left fork");
	pthread_mutex_lock(vars->philo->r_fork);
	print_status(vars, "has taken their right fork");
	print_status(vars, "is eating");
	vars->philo->time_last_eat = get_time();
	vars->philo->times_eaten++;
	sleep_until(get_time() + vars->data->time_to_eat, vars);
	pthread_mutex_unlock(vars->philo->l_fork);
	pthread_mutex_unlock(vars->philo->r_fork);
	if (vars->philo->times_eaten == vars->data->max_eat)
	{
		pthread_mutex_lock(&vars->data->m_fullamount);
		vars->data->full_amount++;
		pthread_mutex_unlock(&vars->data->m_fullamount);
	}
	pthread_mutex_lock(&vars->data->m_fullamount);
	if (vars->data->has_died
		|| vars->data->full_amount == vars->data->num_of_philos)
	{
		pthread_mutex_unlock(&vars->data->m_fullamount);
		return ;
	}
	pthread_mutex_unlock(&vars->data->m_fullamount);
	action_sleep(vars);
}

void	action_sleep(t_vars *vars)
{
	print_status(vars, "is sleeping");
	sleep_until(get_time() + vars->data->time_to_sleep, vars);
	pthread_mutex_lock(&vars->data->m_fullamount);
	if (vars->data->has_died
		|| vars->data->full_amount == vars->data->num_of_philos)
	{
		pthread_mutex_unlock(&vars->data->m_fullamount);
		return ;
	}
	pthread_mutex_unlock(&vars->data->m_fullamount);
	action_think(vars, vars->data->time_to_eat
		* (1 + (vars->data->num_of_philos % 2)) - vars->data->time_to_sleep);
}

void	action_die(t_vars *vars)
{
	pthread_mutex_lock(&vars->data->m_death);
	if (!vars->data->has_died)
	{
		printf("%lu\t\t%d\t has died\n",
			get_time() - vars->philo->start_time, vars->philo->id);
		vars->data->has_died = 1;
	}
	pthread_mutex_unlock(&vars->data->m_death);
}
