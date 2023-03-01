/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmeftah <hmeftah@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 11:56:40 by hmeftah           #+#    #+#             */
/*   Updated: 2023/03/01 17:02:49 by hmeftah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

int	check_last_time_eaten(t_philo *philo, t_args *args)
{
	int	success;

	success = 0;
	gettime(args);
	if (args->ts_ms - philo->lt_eaten >= args->t_die && args->kill_all == false)
	{
		gettime(philo->args);
		printf("%lld %d died\n", philo->args->ts_ms, philo->id);
		success = pthread_mutex_unlock(&philo->mutex);
		success = pthread_mutex_unlock(philo->lmutex);
		pthread_detach(philo->thread);
		args->kill_all = true;
	}
	return (success);
}

void	check_times_eaten(t_philo *philo, t_args *args)
{
	if (args->nt_eat > 0)
		if (philo->t_eaten >= args->nt_eat)
			philo->full = true;
}

void	monitor_philosophers(t_args *args, t_philo **philo)
{
	int					i;

	i = -1;
	while (1)
	{
		i = -1;
		if (args->e_philos >= args->n_philos)
		{
			end_simulation(args, philo);
			return ;
		}
		while (++i < args->n_philos)
		{
			check_last_time_eaten(philo[i], args);
			check_times_eaten(philo[i], args);
		}
	}
}
