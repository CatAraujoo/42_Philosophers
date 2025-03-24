/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmatos-a <cmatos-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 11:56:49 by catarina          #+#    #+#             */
/*   Updated: 2025/03/24 15:30:21 by cmatos-a         ###   ########.fr       */
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
	/*philo->fork_l = &forks[(position + 1) % philo_nbr];
	philo->fork_r = &forks[position];
	if (philo->philo_id % 2 == 0)
	{
		philo->fork_r = &forks[position];
		philo->fork_l = &forks[(position + 1) % philo_nbr];
	}*/
	if (philo->philo_id % 2 != 0) //If ph_id is odd
	{
		philo->fork_l = &forks[(position + 1) % philo_nbr];
		philo->fork_r = &forks[position];
	}
	if (philo->philo_id % 2 == 0) //If ph_id is even, right and left forks are swapped to prevent deadlocks. See #1
	{
		philo->fork_l = &forks[position];
		philo->fork_r = &forks[(position + 1) % philo_nbr];
	}
}

static void	philo_init(t_table *table)
{
	int		i;
	t_philo	*philo;
	
	i = 0;
	while (i < table->n_philo)
	{
		philo = table->philos + i;
		philo->philo_id = i + 1;
		philo->philo_full = false;
		philo->meals = 0;
		safe_mutex(&philo->philo_mutex, INIT);
		philo->table = table;
		printf ("%ld \n", philo->table->n_philo);
		assign_forks(philo, philo->table->forks, i); //VERIFICAR SE HA MAIS ERROS DESTES (TABLE->FORKS EM VEZ DE PHILO->TABLE->FORKS)
		i++;
	}
}

void	ft_init(t_table *table)
{
	int	i;

	i = 0;
	table->end_t = false;
	table->start_t = get_time(MILLISECOND);
	table->all_threads_ready = false;
	table->n_threads_run = 0;
	table->philos = safe_malloc(table->n_philo);
	safe_mutex(&table->table_mutex, INIT);
	safe_mutex(&table->write_mutex, INIT);
	table->forks = safe_malloc(sizeof(t_fork) * table->n_philo);
	while (i < table->n_philo)
	{
		pthread_mutex_init(&table->forks[i].fork, NULL);//Initialize the mutex for each fork in the fork mutex array
		//safe_mutex(&table->forks[i].fork, INIT);
		table->forks[i].fork_id = i; // for each fork/mutex, set the fork_id value
		i++;
	}
	philo_init(table);//initialize
}


