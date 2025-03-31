/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmatos-a <cmatos-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 11:56:49 by catarina          #+#    #+#             */
/*   Updated: 2025/03/31 13:56:09 by cmatos-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	assign_forks(t_table *table, int pos)
{
	while (pos < table->n_philo - 1)
	{
		if (pos % 2)
		{
			table->philos[pos].fork[LEFT] = &table->forks[pos - 1];
			table->philos[pos].fork[RIGHT] = &table->forks[pos];
		}
		else
		{
			table->philos[pos].fork[LEFT] = &table->forks[pos];
			table->philos[pos].fork[RIGHT] = &table->forks[pos + 1];
		}
		pos++;
	}
	if (pos % 2)
	{
		table->philos[pos].fork[LEFT] = &table->forks[pos - 1];
		table->philos[pos].fork[RIGHT] = &table->forks[pos];
	}
	else
	{
		table->philos[pos].fork[LEFT] = &table->forks[pos];
		table->philos[pos].fork[RIGHT] = &table->forks[0];
	}
}

static void	philo_init(t_table *table)
{
	int		i;

	i = 0;
	while (i < table->n_philo)
	{
		table->philos[i].table = table;
		table->philos[i].philo_id = i + 1;
		table->philos[i].philo_full = false;
		table->philos[i].meals = 0;
		table->philos[i].status = -1;
		table->philos[i].death_t = table->time_to_die;
		pthread_mutex_init(&table->philos[i].lock, NULL);
		i++;
	}
	assign_forks(table, 0);
}

static t_table	*init_threads(t_table *table)
{
	long	i;

	table->end_t = false;
	table->n_philos_full = 0;
	table->threads = safe_malloc(sizeof(pthread_t) * table->n_philo);
	table->forks = safe_malloc(sizeof(pthread_mutex_t) * table->n_philo);
	if (!table->forks || !table->threads)
		return (NULL);
	pthread_mutex_init(&table->lock, NULL);
	pthread_mutex_init(&table->log, NULL);
	pthread_mutex_init(&table->finish_lock, NULL);
	i = 0;
	while (i < table->n_philo)
	{
		pthread_mutex_init(&table->forks[i], NULL);
		i++;
	}
	return (table);
}

t_table	*ft_init(int ac, char **av)
{
	t_table	*table;

	table = safe_malloc(sizeof(t_table));
	table->n_philo = valid_input(av[1]);
	table->time_to_die = valid_input(av[2]);
	table->time_to_eat = valid_input(av[3]);
	table->time_to_sleep = valid_input(av[4]);
	if (ac == 6)
		table->n_limit_meal = valid_input(av[5]);
	else
		table->n_limit_meal = 0;
	if (!table->n_philo || !table->time_to_die
		|| !table->time_to_eat || !table->time_to_sleep)
	{
		ft_free(table);
		return (NULL);
	}
	table->start_t = 0;
	table->philos = safe_malloc(sizeof(t_philo) * table->n_philo);
	if (!table->philos)
		return (NULL);
	table = init_threads(table);
	philo_init(table);
	return (table);
}
