/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmatos-a <cmatos-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 13:27:53 by cmatos-a          #+#    #+#             */
/*   Updated: 2025/03/20 14:54:48 by cmatos-a         ###   ########.fr       */
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

static bool	philo_died(t_philo *philo)
{
	long	elapsed;

	if (get_bool(&philo->philo_mutex, &philo->philo_full))
		return (false);
	elapsed = get_time(MILLISECOND) - get_long(&philo->philo_mutex, &philo->last_meal_t);
	if (elapsed > (philo->table->time_to_die / 1000))
		return (true);
	return (false);
}

void	*dinner_simulation(void *data)
{
	t_philo		*philo;
	bool	simulation_finished(t_table *table);
	philo = (t_philo *)data;
	wait_all_threads(philo->table);

	//set time last meal
	set_long(&philo->philo_mutex, &philo->last_meal_t, get_time(MILLISECOND));
	
	//synchro with monitor
	//increase a table variable counter, with all threads running
	increase_long(&philo->table->table_mutex, &philo->table->n_threads_run);
	
	//set last meal time

	while (!get_bool(&philo->table->table_mutex, &philo->table->end_t))
	{
		if (philo->philo_full)
			break ;
		ft_eat(philo);
		write_status(SLEEPING, philo);
		usleep(200);
		//ft_sleeping(philo);
		ft_thinking(philo);
	}
	return (0);//check if correct
}

void	dinner_start(t_table *table)
{
	int	i;
	
	i = -1;
	if (table->n_limit_meal == 0)
		return ; // back to main, clean
	else if (table->n_philo == 1)
		safe_thread(&table->philos[0].thread_id, lone_philo, &table->philos[0], CREATE);
	else
	{
		while (++i < table->n_philo)
			safe_thread(&table->philos[i].thread_id, dinner_simulation,
				&table->philos[i], CREATE);
	}
	//monitor
	safe_thread(&table->monitor, (void *)monitor_dinner, table, CREATE);
	
	//start simulation
	table->start_t = get_time(MILLISECOND);
	set_bool(&table->table_mutex, &table->all_threads_ready, true);
	//wait for everyone
	i = -1;
	while (++i < table->n_philo)
	safe_thread(&table->philos[i].thread_id, NULL, NULL, JOIN);
	//if we manage to reach this line, all philos are full.
	set_bool(&table->table_mutex, &table->end_t, true);
	safe_thread(&table->monitor, NULL, NULL, JOIN);
}

void	*lone_philo(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	wait_all_threads(philo->table);
	set_long(&philo->philo_mutex, &philo->last_meal_t, get_time(MILLISECOND));
	increase_long(&philo->table->table_mutex, &philo->table->n_threads_run);
	write_status(FORK_L, philo);
	while (!get_bool(&philo->table->table_mutex, &philo->table->end_t))
		usleep(200);
	return (NULL);
}

void	monitor_dinner(void *data)
{
	t_table *table;
	int	i;
	table = (t_table *)data;
	//make sure all philos running
	//spinlock until all threads run
	while (!all_threads_running(&table->table_mutex,
		&table->n_threads_run, table->n_philo))
		;
		while (!get_bool(&table->table_mutex, &table->end_t))
		{
			i = -1;
			while (++i < table->n_philo)
			{
				if (philo_died(table->philos + i) && !get_bool(&table->table_mutex, &table->end_t))
				{
					set_bool(&table->table_mutex, &table->end_t, true);
					write_status(DEATH, table->philos + i);
				}
			}
		}
}
