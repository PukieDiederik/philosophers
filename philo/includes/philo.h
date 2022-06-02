/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drobert- <drobert-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 14:14:06 by drobert-          #+#    #+#             */
/*   Updated: 2022/06/02 13:46:17 by drobert-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>

typedef unsigned long ulong;

typedef enum e_philo_state { thinking, eating, sleeping }	t_philo_state;

/* t_data -- All general data
 *	Start time:		Timestamp of when the program started
 *	Time to die:	Time for a philosopher to die 			 (in milliseconds)
 *
 *	Time to eat:	Time it takes for a philosopher to eat	 (in milliseconds)
 *	Time to eat:	Time it takes for a philosopher to sleep (in milliseconds)
 */
typedef struct s_data
{
	pthread_mutex_t	m_death;
	int 			has_died;
	int				time_to_die;

	int	time_to_eat;
	int	time_to_sleep;
	int	num_of_philos;
	int	max_eat;
	int	full_amount;
}	t_data;

typedef struct s_philo
{
	int				id;
	ulong	time_last_eat;
	int				times_eaten;
	ulong	start_time;

	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
}	t_philo;

typedef struct s_vars
{
	t_philo *philo;
	t_data	*data;
}	t_vars;

// Functions
t_data *data_init(int argc, char **argv);
void	data_destroy(t_data *d);

// Actions
void action_think(t_vars *vars, ulong time);
void action_eat(t_vars *vars);
void action_sleep(t_vars *vars);
void action_die(t_vars *vars);

// Utils
int	ft_isdigit(int c);
int	ft_atoi(const char *str);
ulong get_time(void);
void sleep_until(ulong time, t_vars *v);
void print_status(t_vars *vars, char *str);

#endif