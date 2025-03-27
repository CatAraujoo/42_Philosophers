/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: catarina <catarina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 13:41:48 by catarina          #+#    #+#             */
/*   Updated: 2025/03/26 14:33:00 by catarina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_error(char *error)
{
	printf("%s\n", error);
}

void	*safe_malloc(size_t bytes)
{
	void	*ret;

	ret = malloc(bytes);
	if (!ret)
	{
		ft_error("Error allocating memory.");
		exit(EXIT_FAILURE);
	}
	return (ret);
}

long	get_time(t_time_code time_code)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) != 0)
	{
		ft_error("Error. Gettimeofday failed.");
		return (1);
	}
	if (time_code == MILLISECOND)
		return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
	else if (time_code == MICROSECOND)
		return ((tv.tv_sec * 1000000) + (tv.tv_usec));
	else if (time_code == SECOND)
		return (tv.tv_sec);
	ft_error("Invalid time_code provided to get_time.");
	return (0);
}

bool	end_dinner(t_table *table, t_philo *philo, t_end code)
{
	if (code == FULL)
		return (get_bool(&philo->philo_mutex, &philo->philo_full));
	else if (code == MEAL_END)
		return (get_bool(&table->table_mutex, &table->end_t));
	return (false);
}

void	ft_free(t_table *table)
{
	t_philo	*philo;
	int		i;

	i = -1;
	while (++i < table->n_philo)
	{
		philo = table->philos + i;
		safe_mutex(&philo->philo_mutex, DESTROY);
	}
	safe_mutex(&table->write_mutex, DESTROY);
	safe_mutex(&table->table_mutex, DESTROY);
	free(table->forks);
	free(table->philos);
}
