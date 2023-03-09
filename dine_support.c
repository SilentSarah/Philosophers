/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dine_support.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmeftah <hmeftah@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 19:27:38 by hmeftah           #+#    #+#             */
/*   Updated: 2023/03/09 19:30:27 by hmeftah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

bool	check_philosopher_status(t_philo *philo)
{
	pthread_mutex_lock(&philo->args->status);
	if (philo->args->kill_all == true)
	{
		pthread_mutex_unlock(&philo->mutex);
		pthread_mutex_unlock(philo->lmutex);
		philo->args->e_philos++;
		return (true);
	}
	if (philo->full == true)
	{
		pthread_mutex_unlock(&philo->mutex);
		pthread_mutex_unlock(philo->lmutex);
		philo->args->e_philos++;
		return (true);
	}
	pthread_mutex_unlock(&philo->args->status);
	return (false);
}
