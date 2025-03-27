/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmatos-a <cmatos-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 11:26:23 by catarina          #+#    #+#             */
/*   Updated: 2025/03/27 14:31:49 by cmatos-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_atol(char *s)
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

long	valid_input(char *str)
{
	long	input;

	input = ft_atol(str);
	if (input > INT_MAX) //If the result is greater than INT_MAX, print error and flag the error
	{
		ft_error("Input Error: The value cannot be bigger than INT_MAX");
		return (-1);
	}
	if (input < 1) //If not positive, print error and flag the error
	{
		if (input < 0)
			ft_error("Input Error: Positive values only.");
		else
			ft_error("Input Error: If limit meals exists, should be above 0.");
		return (-1);
	}
	return (input);
}
