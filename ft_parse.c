/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: catarina <catarina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 11:26:23 by catarina          #+#    #+#             */
/*   Updated: 2025/03/17 15:36:55 by catarina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static long		ft_atol(const char *str)
{
	long	res;

	res = 0;
	str = valid_input(str);
	while (ft_is_digit(*str))
	{
		res = res * 10 + (*str - '0');
		str++;
	}
	if (res > INT_MAX)
		ft_error("The value is bigger than the INT_MAX.");
	return (res);
}

static int	ft_is_space(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (0);
	return (1);
}

static int		ft_is_digit(char c)
{
	if (c < '0' && c > '9')// >= <= or just > < ??
		return (0);
	return (1);
}
static char	*valid_input(char *str)
{
	//check for negatives
	//check if legit number ex: +77#$%
	//check for int_max
	//check for len
	int len;
	int	i;
	char *nbr;
	
	len = 0;
	i = 0;
	while (ft_is_space(str[i]) == 0)
		i++;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
		ft_error("Only positive numbers allowed.");
	if (ft_is_digit == 1)
		ft_error("The input is not a digit.");
	nbr = str;
	while (ft_is_digit(str[i]))
		len++;
	if (len > 10)
		ft_error("The value is too big.");
	return (nbr);
}

void	handle_input(t_table *table, char **av)
{
	//integers
	// < int max
	//timestamps > 60ms
	//handle optional meals_required
	table->n_philo = ft_atol(av[1]);
	table->time_to_die = ft_atol(av[2]) * 1000; // *1000 to convert to milliseconds
	table->time_to_eat = ft_atol(av[3]) * 1000;
	table->time_to_sleep = ft_atol(av[4]) * 1000;
	if (table->time_to_die < 60000// 60ms 
		|| table->time_to_eat < 60000
		|| table->time_to_sleep < 60000)
		ft_error("The timestamps should be higher than 60ms.");
	if (av[5]) //check if there is arg 5
		table->n_limit_meal = ft_atol(av[5]);
	else
		table->n_limit_meal = -1; //if there is no av[5] initialize the variable in -1
}
