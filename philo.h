/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmatos-a <cmatos-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 11:44:14 by catarina          #+#    #+#             */
/*   Updated: 2025/03/25 14:00:44 by cmatos-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <limits.h>
# include <errno.h>

typedef pthread_mutex_t	t_mtx;
typedef struct s_table	t_table;

typedef enum e_code
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH,
}			t_code;

typedef enum e_actions
{
	DEATH,
	EATING,
	SLEEPING,
	THINKING,
	FORK_L,
	FORK_R,
	FULL,
}			t_actions;

typedef enum e_time_code
{
	SECOND,
	MILLISECOND,
	MICROSECOND,
}			t_time_code;

typedef struct s_forks
{
	t_mtx	fork;
	int		fork_id;
}			t_fork;

typedef struct s_philo
{
	int			philo_id;
	int			philo_eat;
	long		meals;
	long		last_meal_t; //time passed from last meal
	bool		philo_full;
	t_fork		*fork_r;
	t_fork		*fork_l;
	t_table		*table;
	t_actions	status;
	t_mtx		philo_mutex;
	pthread_t	thread_id;	//a philo is a thread
}					t_philo;

typedef struct s_table
{
	long		n_philo;
	long		n_philos_full;
	long		time_to_die;
	long		time_to_eat;
	long		time_to_sleep;
	long		n_limit_meal; //[5] | flag if -1
	long		start_t;
	long		n_threads_run;
	bool		end_t; //a philo dies or all philos full
	bool		all_threads_ready;
	t_mtx		table_mutex; //avoid races while reading from table
	t_mtx		write_mutex;
	t_fork		*forks; //array of all forks
	t_philo		*philos; //array of all philos
	pthread_t	monitor;
}			t_table;

/*typedef struct s_data
{
	pthread_t		*table;
	t_philo			*philos;
	int				n_philos;
	int				n_meals;
	int				n_philos_full;
	int				death_t;
	int				eat_t;
	int				sleep_t;
	int				start_t;
	bool			finish;
	pthread_mutex_t	*forks;
	pthread_mutex_t	lock;
	pthread_mutex_t	log;
	pthread_mutex_t	finish_lock;
}					t_data;*/

void	handle_input(t_table *table, char **av);
void	safe_thread(pthread_t *thread, void *(*foo)(void *),
			void *data, t_code code);
void	safe_mutex(t_mtx *mutex, t_code code);
void	ft_error(char *error);
void	*safe_malloc(size_t bytes);

void	ft_init(t_table *table);
void	wait_all_threads(t_table *table);

long	get_time(t_time_code time_code);
void	dinner_start(t_table *table);
void	*dinner_simulation(void *data);

void	set_bool(t_mtx *mutex, bool *dest, bool value);
bool	get_bool(t_mtx *mutex, bool *value);
void	set_long(t_mtx *mutex, long *dest, long value);
long	get_long(t_mtx *mutex, long *value);

bool	all_threads_running(t_mtx *mutex, long *threads, long philo_nbr);
void	active_threads_count(t_mtx *mutex, long *value);

void	*monitor_dinner(void *data);
void	write_status(t_actions action, t_philo *philo);
void	*lone_philo(void *arg);

void	precise_usleep(long usec, t_table *table);
void	ft_free(t_table *table);
void	de_synchronize_philos(t_philo *philo);
bool	philo_died(t_philo *philo);

void	ft_eat(t_philo *philo);
void	ft_thinking(t_philo *philo, bool value);

#endif