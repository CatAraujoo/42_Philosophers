/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmatos-a <cmatos-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 11:44:14 by catarina          #+#    #+#             */
/*   Updated: 2025/03/28 13:42:25 by cmatos-a         ###   ########.fr       */
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

typedef enum e_actions
{
	DEATH,
	EATING,
	SLEEPING,
	THINKING,
	FORK,
}			t_actions;

enum e_forks
{
	LEFT,
	RIGHT,
};

typedef struct s_philo
{
	struct s_table		*table;
	long				philo_id;
	long				meals;
	long 				death_t; //time of death
	//long		last_meal_t; //time passed from last meal
	bool				philo_full;
	t_actions			status;
	t_mtx				lock;
	t_mtx				*fork[2];
}					t_philo;

typedef struct s_table
{
	pthread_t	*threads; //array of all threads
	t_philo		*philos; //array of all philos
	t_mtx		*forks; //array of all forks
	t_mtx		lock;//mutex for forks
	t_mtx		log;//mutex for log
	t_mtx		finish_lock;//mutex for finish
	long		n_philo;
	long		n_philos_full;
	long		time_to_die;
	long		time_to_eat;
	long		time_to_sleep;
	long		n_limit_meal; //[5] | flag if -1
	long		start_t;
	/*long		n_threads_run;
	bool		all_threads_ready;*/
	bool		end_t; //a philo dies or all philos full
}			t_table;

int		handle_input(t_table *table, char **av);
void	ft_error(char *error);
void	ft_free(t_table *table);
void	*safe_malloc(size_t bytes);

long	ft_atol(char *s);
long	valid_input(char *str);
t_table	*ft_init(int ac, char **av);

long	get_time(void);
void	wait_time(t_philo *philo, long time);
int	dinner_start(t_table *table);
void	*dinner_simulation(void *data);

void	write_status(t_philo *philo, t_actions action);
bool	is_solo(t_philo *philo);
bool	is_dead(t_philo *philo);
void	is_full(t_philo *philo);
void	ft_thinking(t_philo *philo);
void	ft_eating(t_philo *philo);
void	ft_sleeping(t_philo *philo);

#endif