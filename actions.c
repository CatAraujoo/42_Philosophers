/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmatos-a <cmatos-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 11:00:59 by cmatos-a          #+#    #+#             */
/*   Updated: 2025/03/27 15:31:03 by cmatos-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	get_fork(t_philo *philo, int fork)
{
	pthread_mutex_lock(philo->fork[fork]);
	if (is_dead(philo))
	{
		pthread_mutex_unlock(philo->fork[fork]);
		return (false);
	}
	write_status(philo, FORK_L);
	return (true);
}

static bool	get_forks(t_philo *philo)
{
	if (!get_fork(philo, FORK_L))
		return (false);
	if (!get_fork(philo, FORK_R))
	{
		pthread_mutex_unlock(philo->fork[LEFT]);
		return (false);
	}
	return (true);
}

void	ft_thinking(t_philo *philo)
{
	if (!is_dead(philo) && philo->status != THINKING)
	{
		philo->status = THINKING;
		write_status(philo, THINKING);
		wait_time(philo, 5);
	}
}

void	ft_sleeping(t_philo *philo)
{
	if (!is_dead(philo) && philo->status != SLEEPING)
	{
		philo->status = SLEEPING;
		write_status(philo, SLEEPING);
		wait_time(philo, 5);
	}
}

void	ft_eating(t_philo *philo)
{
	if (!get_forks(philo))
		return ;
	pthread_mutex_lock(&philo->table->lock);
	philo->death_t = get_time() + philo->table->time_to_die;
	pthread_mutex_unlock(&philo->table->lock);
	philo->status = EATING;
	write_status(philo, EATING);
	philo->meals++;
	wait_time(philo, philo->table->time_to_eat);
	pthread_mutex_unlock(philo->fork[LEFT]);
	pthread_mutex_unlock(philo->fork[RIGHT]);
}
