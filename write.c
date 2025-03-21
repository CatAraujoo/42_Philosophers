/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmatos-a <cmatos-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 14:27:29 by cmatos-a          #+#    #+#             */
/*   Updated: 2025/03/21 11:29:18 by cmatos-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	write_status(t_actions action, t_philo *philo)
{
	long	elapsed;

	elapsed = get_time(MILLISECOND);
	if (philo->philo_full)
		return ;
	safe_mutex(&philo->table->write_mutex, LOCK);

	if ((philo->status == FORK_L || philo->status == FORK_R)
		&& !get_bool(&philo->table->table_mutex, &philo->table->end_t))
		printf ("%ld %d has taken a fork\n", elapsed, philo->philo_id);
	else if (action == EATING && !get_bool(&philo->table->table_mutex, &philo->table->end_t))
		printf ("%ld %d is eating\n", elapsed, philo->philo_id);
	else if (action == SLEEPING && !get_bool(&philo->table->table_mutex, &philo->table->end_t))
		printf ("%ld %d is sleeping\n", elapsed, philo->philo_id);
	else if (action == THINKING && !get_bool(&philo->table->table_mutex, &philo->table->end_t))
		printf ("%ld %d is thinking\n", elapsed, philo->philo_id);
	else if (action == DEATH)
		printf ("%ld %d died\n", elapsed, philo->philo_id);
	safe_mutex(&philo->table->write_mutex, UNLOCK);
}