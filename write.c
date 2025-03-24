/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmatos-a <cmatos-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 14:27:29 by cmatos-a          #+#    #+#             */
/*   Updated: 2025/03/24 12:04:03 by cmatos-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	write_status(t_actions action, t_philo *philo)
{
	long	elapsed;

	elapsed = get_time(MILLISECOND) - philo->table->start_t;
	if (get_bool(&philo->philo_mutex, &philo->philo_full))
		return ;
	else
	{
		safe_mutex(&philo->table->write_mutex, LOCK);
		philo->table->end_t = get_bool(&philo->table->table_mutex,
			&philo->table->end_t);
		if ((action == FORK_L || action == FORK_R)
				&& (philo->table->end_t == false))
			printf("%ld %d has taken a fork\n", elapsed, philo->philo_id);
		else if (action == EATING && (philo->table->end_t == false))
			printf("%ld %d is eating\n", elapsed, philo->philo_id);
		else if (action == SLEEPING && (philo->table->end_t == false))
			printf("%ld %d is sleeping\n", elapsed, philo->philo_id);
		else if (action == THINKING && (philo->table->end_t == false))
			printf("%ld %d is thinking\n", elapsed, philo->philo_id);
		else if (action == DEATH)
			printf("%ld %d died\n", elapsed, philo->philo_id);
	}
	safe_mutex(&philo->table->write_mutex, UNLOCK);
}