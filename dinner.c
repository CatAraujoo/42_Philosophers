/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: catarina <catarina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 10:14:40 by cmatos-a          #+#    #+#             */
/*   Updated: 2025/03/31 11:40:14 by catarina         ###   ########.fr       */
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
	if (philo->philo_id % 2 == 0 && philo->philo_id == philo->table->n_philo)//|| philo->philo_id == philo->table->n_philo)
	{
		ft_thinking(philo);
		usleep(100);
	} //small delay for even philos
	else
		usleep(50); //small delay for odd philos
	if (is_solo(philo))
	{
		return (NULL);
	}
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
	long	i;
	
	table->start_t = get_time();
	if (table->start_t == 0)
		return (1);
	pthread_mutex_lock(&table->lock);
	i = 0;
	while (i < table->n_philo)
	{
		if (pthread_create(&table->threads[i], NULL, dinner_simulation, &table->philos[i]) != 0)
			return 1;
		i++;
	}
	pthread_mutex_unlock(&table->lock);
	i = 0;
	while (i < table->n_philo)
	{
		if (pthread_join(table->threads[i], NULL))
			return 1;
		i++;
	}
	if (table->n_philos_full == table->n_philo)
		printf ("All philos are full\n");
	return (0);
}

