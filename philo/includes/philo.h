/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drobert- <drobert-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 14:14:06 by drobert-          #+#    #+#             */
/*   Updated: 2022/05/23 17:08:40 by drobert-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>

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
	int	time_to_die;

	int	time_to_eat;
	int	time_to_sleep;
	int num_of_philos;
	int max_eat;
}	t_data;

/* t_philo -- Philosopher specific data
 *	id:			Id of the philosopher
 *	state:		state of the philosopher
 *
 *	l_fork / r_fork: pointers to left and right forks
 */
typedef struct s_philo
{
	int				id;
	t_philo_state 	state;
	int				time_last_eat;
	int				times_eaten;
	unsigned long	start_time;

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

// Utils
int	ft_isdigit(int c);
int	ft_atoi(const char *str);
unsigned long get_time(void);

#endif