/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmatos-a <cmatos-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 11:22:00 by cmatos-a          #+#    #+#             */
/*   Updated: 2025/03/27 14:13:50 by cmatos-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	write_status(t_philo *philo, t_actions action)
{
	pthread_mutex_lock(&philo->table->log);
	if (action == DEATH)
		printf ("%ld %ld died\n", get_time() - philo->table->start_t, philo->philo_id);
	else if (action == EATING)
		printf ("%ld %ld is eating\n", get_time() - philo->table->start_t, philo->philo_id);
	else if (action == SLEEPING)
		printf ("%ld %ld is sleeping\n", get_time() - philo->table->start_t, philo->philo_id);
	else if (action == THINKING)
		printf ("%ld %ld is thinking\n", get_time() - philo->table->start_t, philo->philo_id);
	else if ((action == FORK_L || action == FORK_R)
			&& philo->table->end_t == false)
		printf ("%ld %ld has taken a fork\n",
			get_time() - philo->table->start_t, philo->philo_id);
	pthread_mutex_unlock(&philo->table->log);
}