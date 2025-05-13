/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: catarina <catarina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 09:51:24 by cmatos-a          #+#    #+#             */
/*   Updated: 2025/05/13 14:58:57 by catarina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_table		*table;

	if (ac != 5 && ac != 6)
	{
		ft_error("Error! Invalid arguments");
		return (0);
	}
	table = ft_init(ac, av);
	if (table == NULL)
	{
		ft_error("Error: Table initialization failed");
		ft_free(table);
		return (1);	
	}
	dinner_start(table);
	ft_free(table);
	return (0);
}
