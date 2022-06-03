/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drobert- <drobert-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 14:09:00 by drobert-          #+#    #+#             */
/*   Updated: 2022/06/03 14:46:18 by drobert-         ###   ########.fr       */
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
	if (vars->data->num_of_philos % 2
		&& vars->philo->id == vars->data->num_of_philos)
		action_think(vars, vars->data->time_to_eat * 2);
	if (vars->philo->id % 2)
		action_think(vars, vars->data->time_to_eat);
	else
		action_eat(vars);
	return (0);
}

t_philo	*create_philo(int id, t_data *data, pthread_mutex_t *forks)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (0);
	philo->id = id + 1;
	philo->time_last_eat = get_time();
	philo->start_time = get_time();
	philo->times_eaten = 0;
	philo->l_fork = forks + id;
	philo->r_fork = forks + ((id + 1) % data->num_of_philos);
	return (philo);
}

int destroy_forks(pthread_mutex_t *forks, int i)
{
	while (--i >= 0)
		pthread_mutex_destroy(forks + i);
	return (1);
}

int	init_fork_philos(pthread_t *philos, pthread_mutex_t *forks, t_data *data, t_vars *vars)
{
	int		i;

	i = -1;
	while (++i < data->num_of_philos)
		if (pthread_mutex_init(forks + i, 0))
			return (destroy_forks(forks, i));
	i = -1;
	while (++i < data->num_of_philos)
	{
		(vars + i)->philo = create_philo(i, data, forks);
		(vars + i)->data = data;
		pthread_create(philos + i, 0, &philosopher, vars + i);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_vars			*vars;
	t_data			*data;
	pthread_mutex_t	*forks;
	pthread_t		*philosophers;
	int				i;

	if (argc != 5 && argc != 6)
		return (1);
	data = data_init(argc, argv);
	if (!data)
		return (1);
	forks = malloc(sizeof(pthread_mutex_t) * data->num_of_philos);
	philosophers = malloc(sizeof(pthread_t) * data->num_of_philos);
	vars = malloc(sizeof(t_vars) * data->num_of_philos);
	if (!forks || !philosophers || !vars || init_fork_philos(philosophers, forks, data, vars))
	{
		if (vars)
		{
			printf("Hello World!");
			i = -1;
			while (++i < data->num_of_philos)
				free((vars + i)->philo);
		}
		free(vars);
		free(data);
		free(forks);
		free(philosophers);
		return (1);
	}
	i = -1;
	while (++i < data->num_of_philos)
		pthread_join(philosophers[i], 0);
	i = -1;
	while (++i < data->num_of_philos)
		pthread_mutex_destroy(forks + i);
	i = -1;
	while (++i < data->num_of_philos)
		free((vars + i)->philo);
	data_destroy(data);
	free(philosophers);
	free(forks);
	free(vars);
}
