/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drobert- <drobert-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 14:09:00 by drobert-          #+#    #+#             */
/*   Updated: 2022/06/05 15:35:25 by drobert-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include "philo.h"

void	*philosopher(void *v)
{
	t_vars	*vars;

	vars = v;
	vars->philo->start_time = get_time();
	if (vars->data->num_of_philos % 2
		&& vars->philo->id == vars->data->num_of_philos)
		action_think(vars, vars->data->time_to_eat * 2);
	if (vars->philo->id % 2)
		action_think(vars, vars->data->time_to_eat);
	else
		action_eat(vars);
	return (0);
}

t_philo	*create_philo(int id, t_data *data, pthread_mutex_t *forks, t_philo *philo)
{
	philo->id = id + 1;
	philo->time_last_eat = get_time();
	philo->times_eaten = 0;
	philo->l_fork = forks + id;
	philo->r_fork = forks + ((id + 1) % data->num_of_philos);
	return (philo);
}

int destroy_mutexes(pthread_mutex_t *forks, int i)
{
	while (--i >= 0)
		pthread_mutex_destroy(forks + i);
	return (1);
}

int	init_fork_philos(pthread_t *philosophers, pthread_mutex_t *forks, t_data *data, t_vars *vars, t_philo *philos)
{
	int		i;

	i = -1;
	while (++i < data->num_of_philos)
		if (pthread_mutex_init(forks + i, 0))
			return (destroy_mutexes(forks, i));
	i = -1;
	while (++i < data->num_of_philos)
	{
		(vars + i)->philo = create_philo(i, data, forks, philos + i);
		(vars + i)->data = data;
		if (pthread_create(philosophers + i, 0, &philosopher, vars + i))
		{
			pthread_mutex_lock(&data->m_death);
				data->has_died = 1;
			pthread_mutex_unlock(&data->m_death);
			return (destroy_mutexes(forks, data->num_of_philos));
		}
	}
	return (0);
}

//void	free_vars(t_data *data, t_philo *pilos, pthread_t *philosophers, pthread_mutex_t *forks)
//{
//
//}

int	main(int argc, char **argv)
{
	struct s_collections c;
	t_data			*data;
	int				i;

	if (argc != 5 && argc != 6)
		return (1);
	data = data_init(argc, argv);
	if (!data)
		return (1);
	c.forks = malloc(sizeof(pthread_mutex_t) * data->num_of_philos);
	c.philos = malloc(sizeof(t_philo) * data->num_of_philos);
	c.philosophers = malloc(sizeof(pthread_t) * data->num_of_philos);
	c.vars = malloc(sizeof(t_vars) * data->num_of_philos);
	if (!c.forks || !c.philosophers || !c.vars || !c.philos || init_fork_philos(c.philosophers, c.forks, data, c.vars, c.philos))
	{
		free(c.vars);
		free(data);
		free(c.forks);
		free(c.philosophers);
		free(c.philos);
		return (1);
	}
	i = -1;
	while (++i < data->num_of_philos)
		pthread_join(c.philosophers[i], 0);
	i = -1;
	while (++i < data->num_of_philos)
		pthread_mutex_destroy(c.forks + i);
	destroy_mutexes(c.forks, data->num_of_philos);
	free(c.philos);
	free(c.philosophers);
	free(c.forks);
	free(c.vars);
	data_destroy(data);
}
