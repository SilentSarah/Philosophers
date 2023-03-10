/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmeftah <hmeftah@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 16:24:00 by hmeftah           #+#    #+#             */
/*   Updated: 2023/03/10 19:50:59 by hmeftah          ###   ########.fr       */
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
	int				fuel;
	bool			everyone_ate;
	bool			kill_all;
	struct timeval	time;
	pthread_mutex_t	message;
	pthread_mutex_t	status;
	pthread_mutex_t	clock;
	int				e_philos;
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

int			_atoi(const char *str);
long long	gettime(void);
void		msleep(uint32_t milisec);
void		end_simulation(t_args *args, t_philo **philo);
void		paction(int type, int id, t_args *args, t_philo *philo);
bool		load_arguments(t_args *args, char **av);
t_philo		**allocate_memory(t_args *args);
void		load_environment(t_args *args, t_philo **philo);
void		load_mutexes(t_args *args, t_philo **philo);
void		load_philosophers(t_args *args, t_philo **philo);
void		run_monitor(t_args *args, t_philo **philo);
void		*dine(void *context);
bool		is_it_full(t_args *args, t_philo *philo);
bool		should_it_die(t_args *args, t_philo *philo);
void		imprint_philosopher_data(t_philo *philo);
bool		check_if_all_philosophers_died(t_args *args);
bool		check_if_all_philosophers_ate_enough(t_args *args);
#endif