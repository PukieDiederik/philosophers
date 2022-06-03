/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drobert- <drobert-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 14:14:06 by drobert-          #+#    #+#             */
/*   Updated: 2022/06/03 11:39:57 by drobert-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>

typedef unsigned long	t_ulong;

/* t_data -- All general data
 *	Mutex death:		Mutex for dying
 *	Mutex full amount:	Mutex for changing how many people are full
 *
 *	Has died:			Variable to check if any philo has died
 *	Time to die:		Time for a philosopher to die 			 (in milliseconds)
 *
 *	Time to eat:		Time it takes for a philosopher to eat	 (in milliseconds)
 *	Time to sleep:		Time it takes for a philosopher to sleep (in milliseconds)
 *
 *	Number of philos:	Amount of philosophers around the table
 *	Max eat:			Max amount of time a philosopher needs to eat
 *	full_amount:		Number of philos which have reached max_eat
 */
typedef struct s_data
{
	pthread_mutex_t	m_death;
	pthread_mutex_t	m_fullamount;

	int				has_died;
	int				time_to_die;

	int				time_to_eat;
	int				time_to_sleep;

	int				num_of_philos;
	int				max_eat;
	int				full_amount;
}	t_data;

/* t_data -- All general data
 *	id:				Id of the philosopher
 *	time last eat:	Time when the philo last eat
 *	times eaten:	The amount of times a philosopher has eaten
 *	start_time:		when this philo was created
 *
 *	left fork:		A philosophers left fork
 *	left fork:		A philosophers right fork
 */
typedef struct s_philo
{
	int				id;
	t_ulong			time_last_eat;
	int				times_eaten;
	t_ulong			start_time;

	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
}	t_philo;

typedef struct s_vars
{
	t_philo	*philo;
	t_data	*data;
}	t_vars;

// Functions
t_data	*data_init(int argc, char **argv);
void	data_destroy(t_data *d);

// Actions
void	action_think(t_vars *vars, t_ulong time);
void	action_eat(t_vars *vars);
void	action_sleep(t_vars *vars);
void	action_die(t_vars *vars);

// Utils
int		ft_isdigit(int c);
int		ft_atoi(const char *str);
t_ulong	get_time(void);
void	sleep_until(t_ulong time, t_vars *v);
void	print_status(t_vars *vars, char *str);

#endif