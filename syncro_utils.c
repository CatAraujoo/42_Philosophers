/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syncro_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmatos-a <cmatos-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 14:03:36 by cmatos-a          #+#    #+#             */
/*   Updated: 2025/03/20 11:09:13 by cmatos-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	wait_all_threads(t_table *table)
{
	while (!get_bool(&table->table_mutex, &table->all_threads_ready));
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
void	increase_long(t_mtx *mutex, long *value)
{
	safe_mutex(mutex, LOCK);
	(*value)++;
	safe_mutex(mutex, UNLOCK);
}