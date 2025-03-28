/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmatos-a <cmatos-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 10:14:40 by cmatos-a          #+#    #+#             */
/*   Updated: 2025/03/28 15:21:47 by cmatos-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*dinner_simulation(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	pthread_mutex_lock(&philo->lock);
	philo->death_t = philo->table->start_t + philo->table->time_to_die;
	pthread_mutex_unlock(&philo->lock);
	if (is_solo(philo))
	{
		ft_thinking(philo);
		usleep(philo->table->time_to_die * 1000);
		return (NULL);
	}
	if (philo->philo_id % 2 == 0 || philo->philo_id == philo->table->n_philo)//|| philo->philo_id == philo->table->n_philo)
	{
		ft_thinking(philo);
		usleep(100);
	} //small delay for even philos
	else
		usleep(50); //small delay for odd philos
	while (!is_dead(philo))
	{
		ft_eating(philo);
		ft_sleeping(philo);
		ft_thinking(philo);
	}
	return (NULL);
}

int	dinner_start(t_table *table)
{
	int		i;
	
	table->start_t = get_time();
	if (table->start_t == 0)
		return (1);
	i = 0;
	while (i < table->n_philo)
	{
		if (pthread_create(&table->threads[i], NULL, dinner_simulation, (void *)&table->philos[i]) != 0)
		{
			ft_error("Error: Thread creation failed");
			return 1;
		}
		i++;
	}
	i = 0;
	while (i < table->n_philo)
	{
		pthread_join(table->threads[i], NULL);
		i++;
	}
	return (0);
}

