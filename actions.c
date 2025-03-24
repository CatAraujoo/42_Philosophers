/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmatos-a <cmatos-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 14:26:23 by cmatos-a          #+#    #+#             */
/*   Updated: 2025/03/24 14:56:42 by cmatos-a         ###   ########.fr       */
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
	if (!get_time(MILLISECOND)) // Handle potential failure of get_time
	{
		ft_free(philo->table);
		return ;
	}
	philo->meals++;
	precise_usleep(philo->table->time_to_eat, philo->table);
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
	// Calculate available time to think for odd-numbered philosophers
	t_eat = philo->table->time_to_eat;
	t_sleep = philo->table->time_to_sleep;
	t_think = t_eat * 2 - t_sleep;//available time to think
	if (t_think < 0)
		t_think = 0;
	precise_usleep(t_think * 0.3, philo->table); // Replace 0.3 with a named constant
}