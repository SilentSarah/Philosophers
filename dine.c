/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dine.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmeftah <hmeftah@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 17:43:11 by hmeftah           #+#    #+#             */
/*   Updated: 2023/03/09 20:19:39 by hmeftah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

// void	p_eat(t_philo *philo)
// {
// 	if (philo->lt_eaten == 0)
// 	{
// 		gettime(philo->args);
// 		philo->f_eaten = philo->args->ts_ms;
// 		philo->lt_eaten = philo->args->ts_ms;
// 	}
// 	if (philo->full == true || philo->args->kill_all == true)
// 		return ;
// 	philo->lt_eaten = philo->args->ts_ms;
// 	if (!pthread_mutex_lock(&philo->mutex) && philo->args->kill_all == false)
// 		paction(pick_fork, philo->id, philo->args, philo);
// 	if (!pthread_mutex_lock(philo->lmutex) && philo->args->kill_all == false)
// 	{
// 		paction(pick_fork, philo->id, philo->args, philo);
// 		paction(eat, philo->id, philo->args, philo);
// 		philo->args->test_value += 1;
// 		usleep(philo->args->t_eat * 1000);
// 		gettime(philo->args);
// 		philo->lt_eaten = philo->args->ts_ms;
// 		philo->t_eaten++;
// 	}
// }

void	p_eat(t_philo *philo)
{
	if (philo->full == true || philo->args->kill_all == true)
		return ;
	pthread_mutex_lock(&philo->mutex);
	paction(pick_fork, philo->id, philo->args, philo);
	if (philo->args->kill_all == true)
	{
		pthread_mutex_unlock(&philo->mutex);
		return ;
	}
	pthread_mutex_lock(philo->lmutex);
	paction(pick_fork, philo->id, philo->args, philo);
	paction(eat, philo->id, philo->args, philo);
	msleep(philo->args->t_eat);
	philo->lt_eaten = gettime(philo->args);
	philo->t_eaten++;
	if (philo->args->kill_all == true)
	{
		pthread_mutex_unlock(&philo->mutex);
		return ;
	}
}

void	p_sleep(t_philo *philo)
{
	if (philo->args->kill_all == false)
	{
		pthread_mutex_unlock(&philo->mutex);
		pthread_mutex_unlock(philo->lmutex);
		paction(sleeping, philo->id, philo->args, philo);
		msleep(philo->args->t_sleep);
		if (philo->args->nt_eat > 0
			&& philo->t_eaten >= philo->args->nt_eat)
		{	
			philo->args->e_philos += 1;
			philo->full = true;
			return ;
		}
	}
	paction(think, philo->id, philo->args, philo);
}

void	*dine(void *context)
{
	t_philo	*philo;

	philo = (t_philo *)context;
	while (1)
	{
		if (check_philosopher_status(philo) == true)
			return (NULL);
		p_eat(philo);
		p_sleep(philo);
	}
	return (NULL);
}
