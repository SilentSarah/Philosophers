/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmeftah <hmeftah@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 17:00:31 by hmeftah           #+#    #+#             */
/*   Updated: 2023/03/10 13:19:30 by hmeftah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

static int	spaces(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && ((str[i] == '\t' || str[i] == '\n'
				|| str[i] == '\v' || str[i] == '\f'
				|| str[i] == '\r' || str[i] == ' ')))
			i++;
	return (i);
}

int	_atoi(const char *str)
{
	int	res;
	int	i;
	int	neg;

	i = spaces(str);
	neg = 1;
	res = 0;
	if (str[i] && (str[i] == '-' || str[i] == '+'))
	{
		if (str[i] == '-')
			neg = -neg;
		i++;
	}
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10;
		res += str[i] - 48;
		i++;
	}
	return (res * neg);
}

void	paction(int type, int id, t_args *args, t_philo *philo)
{
	pthread_mutex_lock(&args->message);
	if (type == pick_fork)
		printf("%lld %d has taken a fork\n",
			gettime() - philo->f_eaten, id);
	else if (type == eat)
		printf("%lld %d is eating\n",
			gettime() - philo->f_eaten, id);
	else if (type == sleeping)
		printf("%lld %d is sleeping\n",
			gettime() - philo->f_eaten, id);
	else if (type == think)
		printf("%lld %d is thinking\n",
			gettime() - philo->f_eaten, id);
	else if (type == die)
		printf("%lld %d died\n",
			gettime() - philo->f_eaten, id);
	pthread_mutex_unlock(&args->message);
}

void	end_simulation(t_args *args, t_philo **philo)
{
	int	i;

	i = -1;
	while (++i < args->n_philos)
		free(philo[i]);
	free (philo);
}
