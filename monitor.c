/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmeftah <hmeftah@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 13:21:12 by hmeftah           #+#    #+#             */
/*   Updated: 2023/03/10 19:54:04 by hmeftah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

bool	should_it_die(t_args *args, t_philo *philo)
{
	pthread_mutex_lock(&args->status);
	if (gettime() - philo->lt_eaten >= args->t_die)
	{
		if (args->nt_eat > 0)
		{
			if (philo->t_eaten >= args->nt_eat)
			{
				pthread_mutex_unlock(&args->status);
				return (false);
			}
		}
		args->kill_all = true;
		args->e_philos = 0;
		pthread_mutex_unlock(&args->status);
		return (true);
	}
	pthread_mutex_unlock(&args->status);
	return (false);
}

bool	is_it_full(t_args *args, t_philo *philo)
{
	pthread_mutex_lock(&args->status);
	if (args->nt_eat > 0)
	{
		if (philo->t_eaten >= args->nt_eat)
		{
			pthread_mutex_unlock(&args->status);
			return (true);
		}
	}
	pthread_mutex_unlock(&args->status);
	return (false);
}

bool	check_if_all_philosophers_died(t_args *args)
{
	pthread_mutex_lock(&args->status);
	if (args->kill_all == true)
	{
		pthread_mutex_unlock(&args->status);
		return (true);
	}
	pthread_mutex_unlock(&args->status);
	return (false);
}

bool	check_if_all_philosophers_ate_enough(t_args *args)
{
	pthread_mutex_lock(&args->status);
	if (args->nt_eat > 0)
	{
		if (args->everyone_ate == true)
		{
			pthread_mutex_unlock(&args->status);
			return (true);
		}
	}
	pthread_mutex_unlock(&args->status);
	return (false);
}

void	run_monitor(t_args *args, t_philo **philo)
{
	int	i;

	while (1)
	{
		i = -1;
		if (check_if_all_philosophers_died(args)
			|| check_if_all_philosophers_ate_enough(args))
		{
			end_simulation(args, philo);
			return ;
		}
		while (++i < args->n_philos)
		{
			if (should_it_die(args, philo[i]))
				paction(die, philo[i]->id, args, philo[i]);
			if (is_it_full(args, philo[i]))
			{
				pthread_mutex_lock(&args->status);
				philo[i]->full = true;
				pthread_mutex_unlock(&args->status);
			}
		}
	}
}
