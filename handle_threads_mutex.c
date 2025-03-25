/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_threads_mutex.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmatos-a <cmatos-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 10:19:11 by cmatos-a          #+#    #+#             */
/*   Updated: 2025/03/25 15:24:12 by cmatos-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

//create, join, detach
void	safe_thread(pthread_t *thread, void * (*foo)(void *),
		void *data, t_code code)
{
	if (code == CREATE)
	{
		if (pthread_create(thread, NULL, foo, data) != 0)
			ft_error("Error. Thread creation error.");
	}
	else if (code == JOIN)
	{
		if (pthread_join(*thread, NULL) != 0)
			ft_error("Error. Thread join error.");
	}
	else if (code == DETACH)
	{
		if (pthread_detach(*thread) != 0)
			ft_error("Error. Thread detach error.");
	}
	else
		ft_error("Error. Wrong thread code.");
}