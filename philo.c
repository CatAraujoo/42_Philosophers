/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmatos-a <cmatos-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 09:51:24 by cmatos-a          #+#    #+#             */
/*   Updated: 2025/03/27 14:32:18 by cmatos-a         ###   ########.fr       */
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
	dinner_start(table);
	ft_free(table);
}