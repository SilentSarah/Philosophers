/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmeftah <hmeftah@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 16:24:00 by hmeftah           #+#    #+#             */
/*   Updated: 2023/03/06 19:53:00 by hmeftah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h> 
# include <unistd.h>
# include <stdbool.h>

# define GUIDE "./philo <Number of Philosophers> <Time to die> <Time to eat> \
<Time to sleep> <OPTIONAL: Number of times each philosopher will eat>\n"

struct s_args {
	int				n_philos;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				nt_eat;
	long long		ts_ms;
	bool			kill_all;
	struct timeval	time;
	pthread_mutex_t	message;
	int				e_philos;
	int				test_value;
};
typedef struct s_args	t_args;

struct s_philo {
	int				id;
	long long		lt_eaten;
	long long		f_eaten;
	int				t_eaten;
	pthread_t		thread;
	pthread_mutex_t	mutex;
	pthread_mutex_t	*lmutex;
	t_args			*args;
	struct s_philo	**philo;
	bool			die;
	bool			full;
};
typedef struct s_philo	t_philo;

enum e_actions {
	eat,
	sleeping,
	think,
	pick_fork,
	die,
};

int		_atoi(const char *str);
void	gettime(t_args *args);
void	p_eat(t_philo *philo);
void	p_sleep(t_philo *philo);
void	p_think_or_die(t_philo *philo);
void	monitor_philosophers(t_args *args, t_philo **philo);
void	end_simulation(t_args *args, t_philo **philo);
void	paction(int type, int id, t_args *args, t_philo *philo);
#endif