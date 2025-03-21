/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmatos-a <cmatos-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 11:26:23 by catarina          #+#    #+#             */
/*   Updated: 2025/03/21 10:22:46 by cmatos-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


static int	ft_is_space(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (0);
	return (1);
}

static int	ft_is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

//check for negatives, check if legit number ex: +77#$%, check for int_max, check for len
static char	*valid_input(char *str)
{
	int		len;
	int		i;
	char	*nbr;
	
	len = 0;
	i = 0;
	while (str[i])
	{
		while (ft_is_space(str[i]) == 0)
			i++;
		if (str[i] == '+')
			i++;
		else if (str[i] == '-')
			ft_error("Only positive numbers allowed.");
		if (ft_is_digit(str[i]) == 0)
			ft_error("The input is not a digit.");
		nbr = str;
		if (ft_is_digit(str[i]) == 1)
			len++;
		if (len > 10)
			ft_error("The value is too big.");
		i++;
	}
	return (nbr);
}

static long	ft_atol(char *str)
{
	long	res;
	int		i;
	
	res = 0;
	i = 0;
	str = valid_input(str);
	while (ft_is_digit(str[i]))
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	if (res > INT_MAX)
		ft_error("The value is bigger than the INT_MAX.");
	return (res);
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
