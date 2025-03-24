/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syncro_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmatos-a <cmatos-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 14:03:36 by cmatos-a          #+#    #+#             */
/*   Updated: 2025/03/24 12:02:21 by cmatos-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	precise_usleep(long usec, t_table *table)
{
	long	start;
	long	elapsed;
	long	rem;
	
	start = get_time(MICROSECOND);
	while (get_time(MICROSECOND) - start < usec)
	{
		if (get_bool(&table->table_mutex, &table->all_threads_ready))
			break ;
		elapsed = get_time(MICROSECOND) - start;
		rem = usec - elapsed;
		if (rem > 1000)
			usleep(rem / 2);
		else
		{
			while (get_time(MICROSECOND) - start < usec)
				;
		}
	}
}

void	wait_all_threads(t_table *table)
{
	while (!get_bool(&table->table_mutex, &table->all_threads_ready))
		;// wait untill all_threads_ready becomes true
}

bool	all_threads_running(t_mtx *mutex, long *threads, long philo_nbr)
{
	bool	ret;

	ret = false;
	safe_mutex(mutex, LOCK);
	if (*threads == philo_nbr)
		ret = true;
	safe_mutex(mutex, UNLOCK);
	return (ret);
}
//increase threads running
//to synchro with the monitor
void	active_threads_count(t_mtx *mutex, long *value)
{
	safe_mutex(mutex, LOCK);
	(*value)++;
	safe_mutex(mutex, UNLOCK);
}
