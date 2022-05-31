/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drobert- <drobert-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 13:20:54 by drobert-          #+#    #+#             */
/*   Updated: 2022/05/31 13:27:14 by drobert-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

int action_think(t_vars *vars)
{
	printf("%lu\t\t%d\t is thinking\n",
		   get_time() - vars->philo->start_time, vars->philo->id);
	sleep_until(get_time() + vars->data->time_to_eat + vars->data->time_to_sleep, vars);
	vars->philo->state = eating;
	return (0);
}

int action_eat(t_vars *vars)
{
	pthread_mutex_lock(vars->philo->l_fork);
	printf("%lu\t\t%d\tHas taken their left fork\n",
		   get_time() - vars->philo->start_time, vars->philo->id);
	pthread_mutex_lock(vars->philo->r_fork);
	printf("%lu\t\t%d\tHas taken their right fork\n",
		   get_time() - vars->philo->start_time, vars->philo->id);
	printf("%lu\t\t%d\tis eating\n",
		   get_time() - vars->philo->start_time, vars->philo->id);
	vars->philo->time_last_eat = get_time();
	vars->philo->times_eaten++;
	sleep_until(get_time() + vars->data->time_to_eat, vars);
	pthread_mutex_unlock(vars->philo->l_fork);
	pthread_mutex_unlock(vars->philo->r_fork);
	vars->philo->state = sleeping;
	return (0);
}

int action_sleep(t_vars *vars)
{
	printf("%lu\t\t%d\t is sleeping\n",
		   get_time() - vars->philo->start_time, vars->philo->id);
	sleep_until(get_time() + vars->data->time_to_sleep, vars);
	vars->philo->state = thinking;
	return (0);
}