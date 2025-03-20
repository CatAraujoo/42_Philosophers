/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmatos-a <cmatos-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 14:26:23 by cmatos-a          #+#    #+#             */
/*   Updated: 2025/03/20 14:24:51 by cmatos-a         ###   ########.fr       */
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
	usleep(5); //ft_usleep()?
	if (philo->table->n_limit_meal > 0 && philo->meals == philo->table->n_limit_meal)
		set_bool(&philo->philo_mutex, &philo->philo_full, true);
	
	safe_mutex(&philo->fork_l->fork, UNLOCK);
	safe_mutex(&philo->fork_r->fork, UNLOCK);
}

void	ft_thinking(t_philo *philo)
{
	write_status(THINKING, philo);
}

/*void	ft_sleeping(t_philo *philo)
{
	write_status(SLEEPING, philo);
}*/