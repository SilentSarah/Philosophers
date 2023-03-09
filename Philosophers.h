/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmeftah <hmeftah@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 16:24:00 by hmeftah           #+#    #+#             */
/*   Updated: 2023/03/09 20:26:30 by hmeftah          ###   ########.fr       */
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
	pthread_mutex_t	status;
	pthread_mutex_t	clock;
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

int			_atoi(const char *str);
long long	gettime(t_args *args);
void		p_eat(t_philo *philo);
void		p_sleep(t_philo *philo);
void		monitor_philosophers(t_args *args, t_philo **philo);
void		end_simulation(t_args *args, t_philo **philo);
void		paction(int type, int id, t_args *args, t_philo *philo);
void		*dine(void *context);
void		load_env_data(t_args *args, t_philo **philo);
void		load_philosopher_data(t_args *args);
void		initialize_data(t_args *args, char **av);
bool		check_philosopher_status(t_philo *philo);
void		msleep(uint32_t mili_sec);
long long	rettime(void);
#endif