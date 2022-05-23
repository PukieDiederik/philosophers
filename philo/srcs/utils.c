/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drobert- <drobert-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 16:21:31 by drobert-          #+#    #+#             */
/*   Updated: 2022/05/23 17:03:13 by drobert-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	long	num;
	int		is_neg;

	num = 0;
	while ((*str >= '\t' && *str <= '\r') || *str == ' ')
		str++;
	is_neg = 1;
	if (*str == '-')
	{
		is_neg = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
		num = (num * 10) + (*str++ - '0');
	return (num * is_neg);
}

unsigned long get_time(void)
{
	struct timeval	tval;

	if (gettimeofday(&tval,0) < 0)
		return (0);
	return ((tval.tv_sec * 1000) + (tval.tv_usec / 1000));
}