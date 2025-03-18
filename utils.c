/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: catarina <catarina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 13:41:48 by catarina          #+#    #+#             */
/*   Updated: 2025/03/18 14:04:00 by catarina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_error(char *error)
{
	printf("%s\n", error);
	exit (EXIT_FAILURE);
}
void	*safe_malloc(size_t bytes)
{
	void	*ret;
	
	ret = malloc(bytes);
	if (!ret)
		ft_error("Error allocating memory.");
	return (ret);
}

static void	handle_mutex_error(int status, t_code code) //recreating perror function
{
	if (status == 0)
		return ;
	if (status == EINVAL && (code == LOCK || code == UNLOCK))
		ft_error("The value specified by mutex is invalid.");
	else if (status == EINVAL && code == INIT)
		ft_error("The value specified by attr is invalid.");
	else if (status == EDEADLK)
		ft_error
		("A deadlock would occur if the thread blocked waiting for mutex.");
	else if (status == EPERM)
		ft_error("The current thread does not hold a lock on mutex.");
	else if (status == ENOMEM)
		ft_error
		("The process annot allocate enough memory to create another mutex.");
	else if (status == EBUSY)
		ft_error("Mutex is locked.");
}

//init, destroy, lock, unlock
void	safe_mutex(t_mtx *mutex, t_code code)
{
	if (code == LOCK)
		handle_mutex_error(pthread_mutex_lock(mutex), code);
	else if (code == UNLOCK)
		handle_mutex_error(pthread_mutex_unlock(mutex), code);
	else if (code == INIT)
		handle_mutex_error(pthread_mutex_init(mutex, NULL), code);
	else if (code == DESTROY)
		handle_mutex_error(pthread_mutex_destroy(mutex), code);
	else
		ft_error("Wrong code for mutex handle.");
}
static void	handle_thread_error(int status, t_code code) //recreating perror function
{
	if (status == 0)
		return ;
	if (status == EAGAIN)
		ft_error("No resources to create another thread.");
	else if (status == EPERM)
		ft_error("The caller does not have appropriate permission.");
	else if (status == EINVAL)
		ft_error("The value specified by attr is invalid.");
	else if (status == EINVAL && (code == JOIN || code == DETACH))
		ft_error("The value specified by thread is not joinable.");
	else if (status == ESRCH)
		ft_error
		("No thread found corresponding.");
	else if (status == EDEADLK)
		ft_error
		("A deadlock was detected or the value of thread specifies the calling thread."); //too big
}

//create, join, detach
void	safe_thread(pthread_t *thread, void *(*foo)(void *),
		void *data, t_code code)
{
	if (code == CREATE)
		handle_thread_error(pthread_create(thread, NULL, foo, data), code);
	else if (code == JOIN)
		handle_thread_error(pthread_join(*thread, NULL), code);
	else if (code == DETACH)
		handle_thread_error(pthread_detach(*thread), code);
	else
		ft_error("Wrong code for thread handle. Use CREATE, JOIN or DETACH.");
}