/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmatos-a <cmatos-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 11:31:55 by cmatos-a          #+#    #+#             */
/*   Updated: 2025/03/28 14:56:48 by cmatos-a         ###   ########.fr       */
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

void	wait_time(t_philo *philo, long time)//disapear??
{
	//const long	start = get_time();

	/*while (!is_dead(philo) && (get_time() - start) < time)
		usleep(100);*/
	if ((get_time() + time) >= philo->table->time_to_die)
		usleep((philo->table->time_to_die - get_time()) * 1000);
	else
		usleep(time * 1000);
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
	if (table->threads)
	{
		i = 0;
		while (i < table->n_philo)
		{
			pthread_detach(table->threads[i]);
			i++;
		}
	}
	if(table->forks)
	{
		i = 0;
		while (i < table->n_philo)
		{
			pthread_mutex_destroy(&table->forks[i]);
			i++;
		}
	}
	i = 0;
	while (i < table->n_philo)
	{
		pthread_mutex_destroy(&table->philos[i].lock);
		i++;
	}
	free(table->philos);
	free(table->threads);
	free(table->forks);
	pthread_mutex_destroy(&table->log);
	pthread_mutex_destroy(&table->finish_lock);
	pthread_mutex_destroy(&table->lock);
	free(table);
}
