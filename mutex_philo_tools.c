/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_philo_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmeftah <hmeftah@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 13:02:46 by hmeftah           #+#    #+#             */
/*   Updated: 2023/03/10 15:50:11 by hmeftah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

void	load_mutexes(t_args *args, t_philo **philo)
{
	int	i;

	i = -1;
	while (++i < args->n_philos)
		memset(philo[i], 0, sizeof(t_philo));
	i = -1;
	while (++i < args->n_philos)
		pthread_mutex_init(&philo[i]->mutex, NULL);
	i = -1;
	while (++i < args->n_philos)
		philo[i]->lmutex = &philo[(i + 1) % args->n_philos]->mutex;
	pthread_mutex_init(&args->status, NULL);
	pthread_mutex_init(&args->message, NULL);
}

void	load_philosophers(t_args *args, t_philo **philo)
{
	int			i;
	long long	creation_time;

	i = -1;
	creation_time = gettime();
	while (++i < args->n_philos)
	{
		philo[i]->f_eaten = creation_time;
		philo[i]->lt_eaten = creation_time;
		philo[i]->args = args;
		philo[i]->id = i + 1;
	}
	i = -1;
	while (++i < args->n_philos)
	{
		pthread_create(&philo[i]->thread, NULL, &dine, philo[i]);
		msleep(1);
	}
}
