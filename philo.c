/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmatos-a <cmatos-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 13:40:13 by catarina          #+#    #+#             */
/*   Updated: 2025/03/25 12:27:05 by cmatos-a         ###   ########.fr       */
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
		ft_free(&table);
	}
	else
		ft_error("Invalid number of arguments");
	return (0);
}
