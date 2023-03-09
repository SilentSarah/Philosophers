/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmeftah <hmeftah@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 19:07:00 by hmeftah           #+#    #+#             */
/*   Updated: 2023/03/09 20:26:24 by hmeftah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

void	load_philosopher_data(t_args *args)
{
	int		i;
	t_philo	**philo;

	i = -1;
	philo = (t_philo **)malloc(sizeof(t_philo *) * args->n_philos);
	if (!philo)
		return ;
	while (++i < args->n_philos)
	{
		philo[i] = (t_philo *)malloc(sizeof(t_philo));
		if (!philo[i])
		{
			i = -1;
			while (++i < args->n_philos)
				if (philo[i])
					free(philo[i]);
			free (philo);
			return ;
		}
	}
	load_env_data(args, philo);
	return ;
}

void	initialize_data(t_args *args, char **av)
{
	args->n_philos = _atoi(av[1]);
	args->t_die = _atoi(av[2]);
	args->t_eat = _atoi(av[3]);
	args->t_sleep = _atoi(av[4]);
	if (av[5])
		args->nt_eat = _atoi(av[5]);
	else
		args->nt_eat = -1;
	if (args->n_philos <= 0 || args->t_die <= 0 || args->t_eat <= 0
		|| args->t_sleep <= 0 || args->nt_eat == 0)
	{
		printf(GUIDE);
		return ;
	}
	else
		load_philosopher_data(args);
	return ;
}

long long	rettime(void)
{
	struct timeval	time;
	long long		ts_ms;

	gettimeofday(&time, NULL);
	ts_ms = ((long long)time.tv_sec * 1000)
		+ ((long long)time.tv_usec / 1000);
	return (ts_ms);
}

void	msleep(uint32_t mili_sec)
{
	long long		start;
	long long		ts_ms;

	ts_ms = rettime();
	start = ts_ms;
	while (1)
	{
		usleep(100);
		ts_ms = rettime();
		if (ts_ms - start >= mili_sec)
			return ;
	}
}
