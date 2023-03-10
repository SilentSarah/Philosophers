/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmeftah <hmeftah@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 12:48:24 by hmeftah           #+#    #+#             */
/*   Updated: 2023/03/10 19:34:19 by hmeftah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

bool	load_arguments(t_args *args, char **av)
{
	args->n_philos = _atoi(av[1]);
	args->t_die = _atoi(av[2]);
	args->t_eat = _atoi(av[3]);
	args->t_sleep = _atoi(av[4]);
	if (av[5])
	{
		args->nt_eat = _atoi(av[5]);
		args->fuel = args->nt_eat * args->n_philos;
		args->everyone_ate = false;
	}
	else
		args->nt_eat = -1;
	if (args->n_philos <= 0 || args->t_die <= 0 || args->t_eat <= 0
		|| args->t_sleep <= 0 || (args->nt_eat == 0 || args->nt_eat < -1))
	{
		printf(GUIDE);
		return (false);
	}
	return (true);
}

t_philo	**allocate_memory(t_args *args)
{
	int		i;
	t_philo	**philo;

	i = -1;
	philo = (t_philo **)malloc(sizeof(t_philo *) * args->n_philos);
	if (!philo)
	{
		printf("Error: Cannot allocate memory.\n");
		return (NULL);
	}
	while (++i < args->n_philos)
	{
		philo[i] = (t_philo *)malloc(sizeof(t_philo));
		if (!philo[i])
		{
			i = -1;
			while (++i < args->n_philos)
				if (philo[i])
					free (philo[i]);
			free (philo);
			printf("Error: Cannot allocate memory.\n");
			return (NULL);
		}
	}
	return (philo);
}

void	load_environment(t_args *args, t_philo **philo)
{
	load_mutexes(args, philo);
	load_philosophers(args, philo);
	run_monitor(args, philo);
}
