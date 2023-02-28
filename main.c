/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmeftah <hmeftah@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 16:43:23 by hmeftah           #+#    #+#             */
/*   Updated: 2023/02/28 20:06:49 by hmeftah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

void	*dine(void *context)
{
	t_philo	*philo;

	philo = (t_philo *)context;
	while (1)
	{
		if (philo->args->kill_all == true)
		{
			pthread_mutex_unlock(&philo->mutex);
			pthread_mutex_unlock(philo->lmutex);
			return (NULL);
		}
		p_eat(philo);
		p_sleep(philo);
		p_think_or_die(philo);
		if (philo->args->nt_eat > 0)
		{
			if (philo->t_eaten >= philo->args->nt_eat)
			{
				pthread_mutex_unlock(&philo->mutex);
				pthread_mutex_unlock(philo->lmutex);
				return (NULL);
			}
		}
	}
	return (NULL);
}

void	load_env_data(t_args *args, t_philo **philo)
{
	int	i;

	i = -1;
	while (++i < args->n_philos)
		pthread_mutex_init(&philo[i]->mutex, NULL);
	i = -1;
	while (++i < args->n_philos)
		philo[i]->lmutex = &philo[(i + 1) % args->n_philos]->mutex;
	i = -1;
	while (++i < args->n_philos)
	{
		philo[i]->id = i + 1;
		philo[i]->t_eaten = 0;
		philo[i]->lt_eaten = 0;
		philo[i]->args = args;
		pthread_create(&philo[i]->thread, NULL, &dine, philo[i]);
		usleep(1000);
	}
	i = -1;
	while (++i < args->n_philos)
		pthread_join(philo[i]->thread, NULL);
}

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
	args->kill_all = false;
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

int	main(int ac, char **av)
{
	t_args	args;

	if (ac < 5 || ac > 6)
	{
		printf(GUIDE);
		return (0);
	}
	else
	{
		initialize_data(&args, av);
	}
	return (0);
}
