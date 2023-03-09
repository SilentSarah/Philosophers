/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmeftah <hmeftah@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 11:56:40 by hmeftah           #+#    #+#             */
/*   Updated: 2023/03/09 20:30:40 by hmeftah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

bool	check_last_time_eaten(t_philo *philo, t_args *args)
{
	long long	ts_ms;

	ts_ms = rettime();
	if (ts_ms - philo->lt_eaten >= args->t_die)
	{
		paction(die, philo->id, args, philo);
		return (true);
	}
	return (false);
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
			pthread_mutex_lock(&args->status);
			if (check_last_time_eaten(philo[i], args) == true)
			{
				args->e_philos = args->n_philos;
				args->kill_all = true;
			}
			pthread_mutex_unlock(&args->status);
		}
	}
}

// I NEED TO WORK ON THE FUCKING DATA RACE
