/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmeftah <hmeftah@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 17:43:11 by hmeftah           #+#    #+#             */
/*   Updated: 2023/02/28 20:06:40 by hmeftah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

void	p_eat(t_philo *philo)
{
	if (philo->args->nt_eat > 0)
		if (philo->t_eaten == philo->args->nt_eat)
			return ;
	philo->lt_eaten = philo->args->ts_ms;
	pthread_mutex_lock(&philo->mutex);
	gettime(philo->args);
	printf("%lld %d has taken a fork\n", philo->args->ts_ms, philo->id);
	pthread_mutex_lock(philo->lmutex);
	gettime(philo->args);
	printf("%lld %d has taken a fork\n", philo->args->ts_ms, philo->id);
	gettime(philo->args);
	printf("%lld %d is eating\n", philo->args->ts_ms, philo->id);
	usleep(philo->args->t_eat * 1000);
	gettime(philo->args);
	philo->t_eaten++;
	philo->lt_eaten = philo->args->ts_ms;
}

void	p_sleep(t_philo *philo)
{
	if (philo->args->nt_eat > 0)
		if (philo->t_eaten == philo->args->nt_eat)
			return ;
	pthread_mutex_unlock(&philo->mutex);
	pthread_mutex_unlock(philo->lmutex);
	gettime(philo->args);
	printf("%lld %d is sleeping\n", philo->args->ts_ms, philo->id);
	usleep(philo->args->t_sleep * 1000);
}

void	p_think_or_die(t_philo *philo)
{
	if (philo->args->nt_eat > 0)
		if (philo->t_eaten == philo->args->nt_eat)
			return ;
	gettime(philo->args);
	printf("%lld %d is thinking\n", philo->args->ts_ms, philo->id);
	if (philo->args->ts_ms - philo->lt_eaten >= philo->args->t_die)
	{
		gettime(philo->args);
		printf("%lld %d died\n", philo->args->ts_ms, philo->id);
		philo->args->kill_all = true;
		return ;
	}
}
