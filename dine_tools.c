/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dine_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmeftah <hmeftah@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 14:22:54 by hmeftah           #+#    #+#             */
/*   Updated: 2023/03/10 19:33:39 by hmeftah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

void	imprint_philosopher_data(t_philo *philo)
{
	pthread_mutex_lock(&philo->args->status);
	philo->lt_eaten = gettime();
	philo->t_eaten += 1;
	if (philo->args->nt_eat > 0)
	{
		philo->args->fuel -= 1;
		if (philo->args->fuel == 0)
			philo->args->everyone_ate = true;
	}
	pthread_mutex_unlock(&philo->args->status);
}
