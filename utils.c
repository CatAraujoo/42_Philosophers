/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmatos-a <cmatos-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 11:31:55 by cmatos-a          #+#    #+#             */
/*   Updated: 2025/03/31 15:32:50 by cmatos-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_error(char *error)
{
	printf("%s\n", error);
	exit(EXIT_FAILURE);
}

void	*safe_malloc(size_t bytes)
{
	void	*ptr;

	ptr = malloc(bytes);
	if (!ptr)
		ft_error("Error: Malloc failed");
	return (ptr);
}

void	wait_time(t_philo *philo, long time)
{
	long	current_t;
	long	end_time;

	current_t = get_time();
	end_time = current_t + time;
	while ((current_t < end_time) && !is_dead(philo))
	{
		usleep(1000);
		current_t = get_time();
	}
	usleep(end_time - current_t);
	/*while ((get_time() + time) < philo->table->time_to_die && !is_dead(philo))
		usleep((philo->death_t - current_t) * 1000);
	//else
	usleep(time * 1000);*/
}

long	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL))
	{
		ft_error("Error: gettimeofday failed");
		return (0);
	}
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	ft_free(t_table *table)
{
	long	i;

	if (!table)
		return ;
	i = 0;
	while (i < table->n_philo)
	{
		pthread_mutex_destroy(&table->forks[i]);
		pthread_mutex_destroy(&table->philos[i].lock);
		i++;
	}
	pthread_mutex_destroy(&table->log);
	pthread_mutex_destroy(&table->finish_lock);
	pthread_mutex_destroy(&table->lock);
	if (table->forks)
		free(table->forks);
	if (table->threads)
		free(table->threads);
	if (table->philos)
		free(table->philos);
	free(table);
}
