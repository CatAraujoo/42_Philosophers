/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmatos-a <cmatos-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 14:26:23 by cmatos-a          #+#    #+#             */
/*   Updated: 2025/03/21 13:31:10 by cmatos-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_eat(t_philo *philo)
{
	safe_mutex(&philo->fork_l->fork, LOCK);
	write_status(FORK_L, philo);
	safe_mutex(&philo->fork_r->fork, LOCK);
	write_status(FORK_R, philo);
	set_long(&philo->philo_mutex, &philo->last_meal_t, get_time(MILLISECOND));
	philo->meals++;
	precise_usleep(philo->table->time_to_eat, philo->table); //ft_usleep()?
	if (philo->table->n_limit_meal > 0 && philo->meals == philo->table->n_limit_meal)
		set_bool(&philo->philo_mutex, &philo->philo_full, true);
	
	safe_mutex(&philo->fork_l->fork, UNLOCK);
	safe_mutex(&philo->fork_r->fork, UNLOCK);
}

void	ft_thinking(t_philo *philo, bool value)
{
	long	t_eat;
	long	t_think;
	long	t_sleep;
	//if even the system is fair
	if (!value)
		write_status(THINKING, philo);
	if (philo->table->n_philo % 2 == 0)
		return ;
	//if odd, not always fair
	t_eat = philo->table->time_to_eat;
	t_sleep = philo->table->time_to_sleep;
	t_think = t_eat * 2 - t_sleep;//available time to think
	if (t_think < 0)
		t_think = 0;
	precise_usleep(t_think * 0.42, philo->table);
}

void	ft_sleeping(t_philo *philo)
{
	write_status(SLEEPING, philo);
}