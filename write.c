/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmatos-a <cmatos-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 14:27:29 by cmatos-a          #+#    #+#             */
/*   Updated: 2025/03/25 17:56:33 by cmatos-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	write_status(t_actions action, t_philo *philo)
{
	long	elapsed;
	bool	end_t;

	elapsed =  get_time(MILLISECOND) - philo->table->start_t;
	if (get_bool(&philo->philo_mutex, &philo->philo_full))
		return ;
	else
	{
		safe_mutex(&philo->table->write_mutex, LOCK);
		end_t = get_bool(&philo->table->table_mutex, &philo->table->end_t);
		if ((action == FORK_L || action == FORK_R) && (end_t == false))
			printf("%ld %d has taken a fork\n", elapsed, philo->philo_id);
		else if (action == EATING && (end_t == false))
		{
			printf("%ld %d is eating\n", elapsed, philo->philo_id);
			if (philo->philo_full == true)
				printf("%ld %d is full\n", elapsed, philo->philo_id);
		}
		else if (action == SLEEPING && (end_t == false))
			printf("%ld %d is sleeping\n", elapsed, philo->philo_id);
		else if (action == THINKING && (end_t == false))
			printf("%ld %d is thinking\n", elapsed, philo->philo_id);
		else if (action == DEATH)
		{
			printf("%ld %d died\n", elapsed, philo->philo_id);
		}
	}
	safe_mutex(&philo->table->write_mutex, UNLOCK);
}

