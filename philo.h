/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: catarina <catarina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 11:44:14 by catarina          #+#    #+#             */
/*   Updated: 2025/03/18 14:05:32 by catarina         ###   ########.fr       */
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

typedef pthread_mutex_t t_mtx;

typedef struct s_forks{
	t_mtx	fork;
	int		fork_id;
}			t_fork;

typedef enum e_code
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH
}			t_code;

enum e_actions{
	DEATH,
	EATING,
	SLEEPING,
	THINKING,
	FORK,
	FULL
};

typedef struct s_table t_table;

typedef struct s_philo
{
	//t_data		*data;
	int			philo_id;
	int			philo_eat;
	long		meals;
	long		last_meal_t; //time passed from last meal
	bool		philo_full;
	t_fork		fork_r;
	t_fork		fork_l;
	pthread_t		thread_id;	//a philo is a thread
	t_table		*table;
}					t_philo;

typedef struct s_table
{
	long	n_philo;
	long	n_philos_full;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	long	n_limit_meal; //[5] | flag if -1
	long	start_t;
	bool	end_t; //a philo dies or all philos full
	t_fork		*forks; //array of all forks
	t_philo		*philos; //array of all philos
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
#endif