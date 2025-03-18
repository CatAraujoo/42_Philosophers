/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: catarina <catarina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 11:56:49 by catarina          #+#    #+#             */
/*   Updated: 2025/03/18 14:18:31 by catarina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_init(t_table *table)
{
	int	i;

	i = -1;
	table->end_t = false;
	table->philos = safe_malloc(table->n_philo);
	table->forks = safe_malloc(sizeof(t_fork) * table->n_philo);
	while(++i < table->n_philo)
	{
		safe_mutex(&table->forks[i].fork, INIT);
		table->forks[i].fork_id = i; // great for debug
	}
	philo_init(table);
}

static void	philo_init(t_table *table)
{
	int	i;
	t_philo		*philo;

	i = -1;
	while (++i < table->n_philo)
	{
		philo = table->philos + i;
		philo->philo_id = i + 1;
		philo->philo_full = false;
		philo->meals = 0;
		philo->table = table;
		//ad hoc						 i = position in the table
		assign_forks(philo, table->forks, i);
	}
}

static void		assign_forks(t_philo *philo, t_fork *forks, int position)
{
	 
}
