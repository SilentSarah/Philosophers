/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmeftah <hmeftah@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 12:45:33 by hmeftah           #+#    #+#             */
/*   Updated: 2023/03/10 15:31:07 by hmeftah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

int	main(int ac, char **av)
{
	t_args	args;
	t_philo	**philo;

	if (ac < 5 || ac > 6)
	{
		printf(GUIDE);
		return (0);
	}
	if (!load_arguments(&args, av))
		return (1);
	philo = allocate_memory(&args);
	if (!philo)
		return (1);
	load_environment(&args, philo);
}
