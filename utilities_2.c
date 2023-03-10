/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmeftah <hmeftah@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 13:11:30 by hmeftah           #+#    #+#             */
/*   Updated: 2023/03/10 13:36:19 by hmeftah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

long long	gettime(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (((long long)time.tv_sec * 1000 + (long long)time.tv_usec / 1000));
}

void	msleep(uint32_t milisec)
{
	long long	start;

	start = gettime();
	while (1)
	{
		usleep(100);
		if (gettime() - start >= milisec)
			return ;
	}
	return ;
}
