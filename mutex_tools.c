/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmeftah <hmeftah@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 18:59:37 by hmeftah           #+#    #+#             */
/*   Updated: 2023/03/09 19:32:53 by hmeftah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

static void	load_mutexes(t_args *args, t_philo **philo)
{
	int	i;

	i = -1;
	while (++i < args->n_philos)
		pthread_mutex_init(&philo[i]->mutex, NULL);
	pthread_mutex_init(&args->message, NULL);
	pthread_mutex_init(&args->clock, NULL);
	i = -1;
	while (++i < args->n_philos)
		philo[i]->lmutex = &philo[(i + 1) % args->n_philos]->mutex;
}

static void	load_philosophers(t_args *args, t_philo **philo)
{
	int	i;	

	i = -1;
	gettime(args);
	while (++i < args->n_philos)
	{
		philo[i]->id = i + 1;
		philo[i]->args = args;
		philo[i]->full = false;
		philo[i]->f_eaten = args->ts_ms;
		philo[i]->lt_eaten = args->ts_ms;
		pthread_create(&philo[i]->thread, NULL, &dine, philo[i]);
		usleep(1000);
	}
}

void	load_env_data(t_args *args, t_philo **philo)
{
	load_mutexes(args, philo);
	pthread_mutex_lock(&args->status);
	args->kill_all = false;
	args->e_philos = 0;
	pthread_mutex_unlock(&args->status);
	load_philosophers(args, philo);
	monitor_philosophers(args, philo);
}
