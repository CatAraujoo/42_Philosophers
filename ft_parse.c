/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmatos-a <cmatos-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 11:26:23 by catarina          #+#    #+#             */
/*   Updated: 2025/03/25 14:02:13 by cmatos-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static long	ft_atol(char *s)
{
	long		res;

	res = 0;
	while ((*s == '+' || *s == 32 || (*s >= 9 && *s <= 13)))
		s++;
	if (*s == '-')
		return (-1);
	if (!(*s >= '0' && *s <= '9'))
	{
		ft_error("Input Error: Only digits are allowed.");
		exit(EXIT_FAILURE);
	}
	while (*s >= '0' && *s <= '9')
		res = (res * 10) + (*s++ - '0');
	return (res);
}

static long	valid_input(char *str)
{
	long	input;

	input = ft_atol(str);
	if (input > INT_MAX) //If the result is greater than INT_MAX, print error and flag the error
	{
		ft_error("Input Error: The value cannot be bigger than INT_MAX");
		exit(EXIT_FAILURE);
	}
	if (input < 1) //If not positive, print error and flag the error
	{
		if (input < 0)
			ft_error("Input Error: Positive values only.");
		else
			ft_error("Input Error: If limit meals exists, should be above 0.");
		exit(EXIT_FAILURE);
	}
	return (input);
}

void	handle_input(t_table *table, char **av)
{
	//integers
	// < int max
	//timestamps > 60ms
	//handle optional meals_required
	table->n_philo = valid_input(av[1]);
	table->time_to_die = valid_input(av[2]) * 1000; // *1000 to convert to milliseconds
	table->time_to_eat = valid_input(av[3]) * 1000;
	table->time_to_sleep = valid_input(av[4]) * 1000;
	if (table->time_to_die < 60000// 60ms 
		|| table->time_to_eat < 60000
		|| table->time_to_sleep < 60000)
	{
		ft_error("The timestamps should be higher than 60ms.");
		exit(EXIT_FAILURE);
	}
	if (av[5]) //check if there is arg 5
		table->n_limit_meal = valid_input(av[5]);
	else
		table->n_limit_meal = -1; //if there is no av[5] initialize the variable in -1
}
