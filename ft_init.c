/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmatos-a <cmatos-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 11:56:49 by catarina          #+#    #+#             */
/*   Updated: 2025/03/20 14:11:54 by cmatos-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	assign_forks(t_philo *philo, t_fork *forks, int position)
{
	//the fork 0(philo-1) is from philo_id 1
	//every philo takes the left fork first
	//if odd first left, if even first right fork
	int	philo_nbr;

	philo_nbr = philo->table->n_philo;
	philo->fork_l = &forks[(position + 1) % philo_nbr];
	philo->fork_r = &forks[position];
	if (philo->philo_id % 2 == 0)
	{
		philo->fork_r = &forks[position];
		philo->fork_l = &forks[(position + 1) % philo_nbr];
	}

}

static void	philo_init(t_table *table)
{
	int		i;
	t_philo	*philo;
	
	i = -1;
	while (++i < table->n_philo)
	{
		philo = table->philos + i;
		philo->philo_id = i + 1;
		philo->philo_full = false;
		philo->meals = 0;
		philo->table = table;
		safe_mutex(&philo->philo_mutex, INIT);
		//ad hoc						 i = position in the table
		assign_forks(philo, table->forks, i);
	}
}

void	ft_init(t_table *table)
{
	int	i;

	i = -1;
	table->end_t = false;
	table->all_threads_ready = false;
	table->philos = safe_malloc(table->n_philo);
	safe_mutex(&table->table_mutex, INIT);
	table->forks = safe_malloc(sizeof(t_fork) * table->n_philo);
	while (++i < table->n_philo)
	{
		pthread_mutex_init(&table->forks[i].fork, NULL);//null??
		safe_mutex(&table->forks[i].fork, INIT);
		table->forks[i].fork_id = i; // great for debug
	}
	philo_init(table);
}


