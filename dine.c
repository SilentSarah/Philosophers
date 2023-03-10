/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dine.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmeftah <hmeftah@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 13:37:44 by hmeftah           #+#    #+#             */
/*   Updated: 2023/03/10 19:51:42 by hmeftah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

static void	philo_eat(t_philo *philo)
{
	if (is_it_full(philo->args, philo))
		return ;
	pthread_mutex_lock(&philo->mutex);
	paction(pick_fork, philo->id, philo->args, philo);
	if (should_it_die(philo->args, philo))
	{
		pthread_mutex_unlock(&philo->mutex);
		return ;
	}
	pthread_mutex_lock(philo->lmutex);
	paction(pick_fork, philo->id, philo->args, philo);
	paction(eat, philo->id, philo->args, philo);
	msleep(philo->args->t_eat);
	imprint_philosopher_data(philo);
}

static void	philo_sleep(t_philo *philo)
{
	pthread_mutex_unlock(&philo->mutex);
	pthread_mutex_unlock(philo->lmutex);
	paction(sleeping, philo->id, philo->args, philo);
	msleep(philo->args->t_eat);
}

static void	philo_think(t_philo *philo)
{
	paction(think, philo->id, philo->args, philo);
}

void	*dine(void *context)
{
	t_philo	*philo;

	philo = (t_philo *)context;
	while (1)
	{
		if (is_it_full(philo->args, philo)
			|| check_if_all_philosophers_died(philo->args))
			return (NULL);
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
}
