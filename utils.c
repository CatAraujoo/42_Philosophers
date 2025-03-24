/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmatos-a <cmatos-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 13:41:48 by catarina          #+#    #+#             */
/*   Updated: 2025/03/24 15:04:59 by cmatos-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_error(char *error)
{
	printf("%s\n", error);
}

void	*safe_malloc(size_t bytes)
{
	void	*ret;

	ret = malloc(bytes);
	if (!ret)
	{
		ft_error("Error allocating memory.");
		exit(EXIT_FAILURE);
	}
	return (ret);
}

long	get_time(t_time_code time_code)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
	{
		ft_error("Gettimeofday failed.");
		return (0);
	}
	if (time_code == SECOND)
		return (tv.tv_sec);
	else if (time_code == MILLISECOND)
		return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
	else if (time_code == MICROSECOND)
		return ((tv.tv_sec * 1000000) + tv.tv_usec);
	ft_error("Invalid time_code provided to get_time.");
	return (0);
}

static void	handle_mutex_error(int status, t_code code) //recreating perror function
{
	if (status != 0 && (code == LOCK || code == UNLOCK 
			|| code == INIT || code == DESTROY))
	{
		if (code == LOCK)
			ft_error("Mutex lock error.");
		else if (code == UNLOCK)
			ft_error("Mutex unlock error.");
		else if (code == INIT)
			ft_error("Mutex initialization error.");
		else if (code == DESTROY)
			ft_error("Mutex destruction error.");
		return ;
	}
	return;
}
//init, destroy, lock, unlock
void	safe_mutex(t_mtx *mutex, t_code code)
{
	int	status;

	if (code == LOCK)
		status = pthread_mutex_lock(mutex);
	else if (code == UNLOCK)
		status = pthread_mutex_unlock(mutex);
	else if (code == INIT)
		status = pthread_mutex_init(mutex, NULL);
	else if (code == DESTROY)
		status = pthread_mutex_destroy(mutex);
	else
	{
		ft_error("Invalid code for mutex operation.");
		return ;
	}
	handle_mutex_error(status, code);
}

static int	handle_thread_error(int status, t_code code)
{
	if (status != 0 && (code == CREATE || code == JOIN || code == DETACH))
	{
		if (code == CREATE)
			ft_error("Thread creation error.");
		else if (code == JOIN)
			ft_error("Thread join error.");
		else if (code == DETACH)
			ft_error("Thread detach error.");
		return (status);
	}
	return (0);
}

//create, join, detach
void	safe_thread(pthread_t *thread, void * (*foo)(void *),
		void *data, t_code code)
{
	int	status;

	if (code == CREATE)
		status = pthread_create(thread, NULL, foo, data);
	else if (code == JOIN)
		status = pthread_join(*thread, NULL);
	else if (code == DETACH)
		status = pthread_detach(*thread);
	else
	{
		ft_error("Invalid code for thread operation.");
		return ;
	}
	handle_thread_error(status, code);
}

void	ft_free(t_table *table)
{
	t_philo	*philo;
	int		i;

	i = -1;
	while (++i < table->n_philo)
	{
		philo = table->philos + i;
		safe_mutex(&philo->philo_mutex, DESTROY);
	}
	safe_mutex(&table->write_mutex, DESTROY);
	safe_mutex(&table->table_mutex, DESTROY);
	free(table->forks);
	free(table->philos);
}
