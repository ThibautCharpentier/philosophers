/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharpen <tcharpen@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 19:04:48 by tcharpen          #+#    #+#             */
/*   Updated: 2022/07/26 19:04:48 by tcharpen         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	free_all(t_var *var, int error)
{
	free(var->check_fork);
	free(var->philo);
	free(var->last_eat);
	free(var->fork);
	free(var);
	if (error)
		write(2, "malloc error\n", 13);
}

void	destroy_all(t_var *var)
{
	int	i;

	pthread_mutex_destroy(&(var->writing));
	pthread_mutex_destroy(&(var->check_end_eating));
	i = -1;
	while (++i < var->nb_philo)
	{
		pthread_mutex_destroy(&(var->check_fork[i]));
		pthread_mutex_destroy(&(var->last_eat[i]));
	}
}
