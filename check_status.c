/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmatos-a <cmatos-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 10:59:37 by cmatos-a          #+#    #+#             */
/*   Updated: 2025/03/31 15:09:05 by cmatos-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	is_solo(t_philo *philo)
{
	if (philo->table->n_philo == 1)
	{
		pthread_mutex_lock(philo->fork[RIGHT]);
		write_status(philo, FORK);
		pthread_mutex_unlock(philo->fork[RIGHT]);
		while (!is_dead(philo))
			;
		return (true);
	}
	return (false);
}

bool	is_dead(t_philo *philo)
{
	bool	dead;

	dead = false;
	pthread_mutex_lock(&philo->lock);
	pthread_mutex_lock(&philo->table->finish_lock);
	if (get_time() >= philo->death_t || philo->table->end_t)
	{
		if (philo->table->end_t == false)
			write_status(philo, DEATH);
		philo->table->end_t = true;
	}
	pthread_mutex_lock(&philo->table->lock);
	is_full(philo);
	if (philo->table->n_philos_full == philo->table->n_philo)
		philo->table->end_t = true;
	dead = philo->table->end_t;
	pthread_mutex_unlock(&philo->table->lock);
	pthread_mutex_unlock(&philo->table->finish_lock);
	pthread_mutex_unlock(&philo->lock);
	return (dead);
}

void	is_full(t_philo *philo)
{
	if (philo->meals >= philo->table->n_limit_meal
		&& philo->table->n_limit_meal != 0 && (philo->philo_full == false))
	{
		philo->table->n_philos_full++;
		philo->philo_full = true;
	}
}
