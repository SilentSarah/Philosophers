/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmeftah <hmeftah@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 17:43:11 by hmeftah           #+#    #+#             */
/*   Updated: 2023/03/01 16:05:32 by hmeftah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

void	p_eat(t_philo *philo)
{
	if (philo->full == true || philo->args->kill_all == true)
		return ;
	if (philo->lt_eaten == 0)
	{
		gettime(philo->args);
		philo->lt_eaten = philo->args->ts_ms;
	}
	philo->lt_eaten = philo->args->ts_ms;
	if (!pthread_mutex_lock(&philo->mutex) && philo->args->kill_all == false)
	{
		gettime(philo->args);
		printf("%lld %d has taken a fork\n", philo->args->ts_ms, philo->id);
	}
	if (!pthread_mutex_lock(philo->lmutex) && philo->args->kill_all == false)
	{
		gettime(philo->args);
		printf("%lld %d has taken a fork\n", philo->args->ts_ms, philo->id);
		gettime(philo->args);
		printf("%lld %d is eating\n", philo->args->ts_ms, philo->id);
		philo->args->test_value += 1;
		usleep(philo->args->t_eat * 1000);
		gettime(philo->args);
		philo->lt_eaten = philo->args->ts_ms;
		philo->t_eaten++;
	}
}

void	p_sleep(t_philo *philo)
{
	if ((!pthread_mutex_unlock(&philo->mutex)
			&& !pthread_mutex_unlock(philo->lmutex))
		&& philo->args->kill_all == false)
	{
		gettime(philo->args);
		printf("%lld %d is sleeping\n", philo->args->ts_ms, philo->id);
		usleep(philo->args->t_sleep * 1000);
	}
}

void	p_think_or_die(t_philo *philo)
{
	if (philo->full == true || philo->args->kill_all == true)
		return ;
	gettime(philo->args);
	printf("%lld %d is thinking\n", philo->args->ts_ms, philo->id);
}
