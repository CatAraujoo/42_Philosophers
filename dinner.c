/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmatos-a <cmatos-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 13:27:53 by cmatos-a          #+#    #+#             */
/*   Updated: 2025/03/25 17:55:03 by cmatos-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*if no meals return 0
if only one philo ad hoc function
1 create all threads, all philos
2 create a monitor thread
3 synchronize the beggining of the simulation
pthread_creat -> phio starts running!
every philo start simultaneously
4 join everyone*/

bool	philo_died(t_philo *philo)
{
	long	elapsed;
	
	if (get_bool(&philo->philo_mutex, &philo->philo_full) == true)
		return (true);
	elapsed = get_time(MILLISECOND) - get_long(&philo->philo_mutex,
		&philo->last_meal_t);
	if (elapsed > philo->table->time_to_die) // Ensure time_to_die is in milliseconds
		return (true);
	return (false);
}

void	*dinner_simulation(void *data)
{
	t_philo		*philo;
	bool	simulation_finished(t_table *table);
	philo = (t_philo *)data;
	wait_all_threads(philo->table);
	set_long(&philo->philo_mutex, &philo->last_meal_t, get_time(MILLISECOND));
	//increase a table variable counter, with all threads running
	active_threads_count(&philo->table->table_mutex, &philo->table->n_threads_run);
	de_synchronize_philos(philo);
	while (!get_bool(&philo->table->table_mutex, &philo->table->end_t))
	{
		if (philo->philo_full)
			break ;
		ft_eat(philo);
		write_status(SLEEPING, philo);
		precise_usleep(philo->table->time_to_sleep, philo->table);
		ft_thinking(philo, false);
	}
	return (NULL);
}

void	dinner_start(t_table *table)
{
	int	i;

	i = 0;
	if (table->n_limit_meal == 0)
		return ;
	else if (table->n_philo == 1)	
		safe_thread(&table->philos[0].thread_id, lone_philo, &table->philos[0], CREATE);
	else
	{
		while (i < table->n_philo)
		{
			safe_thread(&table->philos[i].thread_id, dinner_simulation,
				&table->philos[i], CREATE);
			i++;
		}
	}
	safe_thread(&table->monitor, monitor_dinner, table, CREATE);
	table->start_t = get_time(MILLISECOND);
	set_bool(&table->table_mutex, &table->all_threads_ready, true);
	i = 0;
	while (i < table->n_philo)
		safe_thread(&table->philos[i++].thread_id, NULL, NULL, JOIN);
	//if we manage to reach this line, all philos are full.
	set_bool(&table->table_mutex, &table->end_t, true);
	safe_thread(&table->monitor, NULL, NULL, JOIN);
}

void	*lone_philo(void *arg)
{
	t_philo *philo;
	long	current_t;

	philo = (t_philo *)arg;
	wait_all_threads(philo->table);
	current_t = get_time(MILLISECOND);
	set_long(&philo->philo_mutex, &philo->last_meal_t, current_t);//last meal time gets current time
	safe_mutex(&philo->table->table_mutex, LOCK);
	active_threads_count(&philo->table->table_mutex, &philo->table->n_threads_run);
	safe_mutex(&philo->table->table_mutex, UNLOCK);
	write_status(FORK_L, philo);
	while (!philo->table->end_t)
		precise_usleep(philo->table->time_to_die, philo->table);//??
	return (NULL);
}

void	*monitor_dinner(void *data)
{
	t_table	*table;
	int		i;

	table = (t_table *)data;
	while (!all_threads_running(&table->table_mutex, &table->n_threads_run, table->n_philo))
		;
	while (!get_bool(&table->table_mutex, &table->end_t))
	{
		i = 0;
		while (i++ < table->n_philo && !get_bool(&table->table_mutex, &table->end_t))
		{
			if (philo_died(table->philos + i) == true)//check_time_left
			{
				set_bool(&table->table_mutex, &table->end_t, true);
				write_status(DEATH, table->philos + i);
			}
			usleep(50);
			if (get_long(&table->table_mutex, &table->n_philos_full) >= get_long(&table->table_mutex, &table->n_philo))
			{
				set_bool(&table->table_mutex, &table->philos->philo_full, true);
				set_bool(&table->table_mutex, &table->end_t, true);
			}
		}
	}
	return (NULL);
}
