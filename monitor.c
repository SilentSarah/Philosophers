/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmeftah <hmeftah@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 11:56:40 by hmeftah           #+#    #+#             */
/*   Updated: 2023/03/06 20:07:52 by hmeftah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

bool	check_last_time_eaten(t_philo *philo, t_args *args)
{
	int	success;

	success = 0;
	gettime(args);
	if (args->ts_ms - philo->lt_eaten >= args->t_die)
	{
		paction(die, philo->id, args, philo);
		success = pthread_mutex_unlock(&philo->mutex);
		success = pthread_mutex_unlock(philo->lmutex);
		pthread_detach(philo->thread);
		args->kill_all = true;
	}
	return (args->kill_all);
}

void	monitor_philosophers(t_args *args, t_philo **philo)
{
	int					i;

	while (1)
	{
		if (args->e_philos >= args->n_philos)
		{
			end_simulation(args, philo);
			return ;
		}
		i = -1;
		while (++i < args->n_philos)
		{
			if (check_last_time_eaten(philo[i], args) == true)
				args->e_philos = args->n_philos;
		}
	}
}
