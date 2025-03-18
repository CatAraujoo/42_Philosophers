/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: catarina <catarina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 13:40:13 by catarina          #+#    #+#             */
/*   Updated: 2025/03/17 13:49:23 by catarina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_table		table;
	if (ac == 5 || ac == 6)
	{
		handle_input(&table, av);
		ft_init(&table);
		dinner_start(&table);
		ft_free(&table); // if philos are full or 1 philo died
	}
	else
		ft_error("Invalid number of arguments");
	return (0);
}