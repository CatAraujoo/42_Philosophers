/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmatos-a <cmatos-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 11:00:59 by cmatos-a          #+#    #+#             */
/*   Updated: 2025/03/28 15:23:50 by cmatos-a         ###   ########.fr       */
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
	write_status(philo, FORK);
	return (true);
}

static bool	get_forks(t_philo *philo)
{
	if (!get_fork(philo, LEFT))
		return (false);
	if (!get_fork(philo, RIGHT))
	{
		pthread_mutex_unlock(philo->fork[LEFT]);
		return (false);
	}
	return (true);
}

void	ft_thinking(t_philo *philo)
{
	if (!is_dead(philo))// && philo->status != THINKING
	{
		philo->status = THINKING;
		write_status(philo, THINKING);
		wait_time(philo, philo->table->time_to_sleep);//5?
	}
}

void	ft_sleeping(t_philo *philo)
{
	if (!is_dead(philo) && philo->status != SLEEPING)
	{
		philo->status = SLEEPING;
		write_status(philo, SLEEPING);
		wait_time(philo, philo->table->time_to_sleep);//5?
	}
}

void	ft_eating(t_philo *philo)
{
	if (!get_forks(philo))
		return ;
	pthread_mutex_lock(&philo->lock);
	philo->death_t = get_time() + philo->table->time_to_die;
	pthread_mutex_unlock(&philo->lock);
	philo->status = EATING;
	write_status(philo, EATING);
	printf ("HELLLO");
	philo->meals++;
	wait_time(philo, philo->table->time_to_eat);// philo->table->time_to_sleep;
	pthread_mutex_unlock(philo->fork[LEFT]);
	pthread_mutex_unlock(philo->fork[RIGHT]);
}
