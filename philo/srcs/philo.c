/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharpen <tcharpen@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 15:43:08 by tcharpen          #+#    #+#             */
/*   Updated: 2022/08/04 15:43:08 by tcharpen         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	wait_thread(t_var *var)
{
	int	i_philo;

	pthread_mutex_lock(&var->check_end_eating);
	while (var->end_eating < var->nb_philo)
	{
		pthread_mutex_unlock(&var->check_end_eating);
		i_philo = -1;
		while (++i_philo < var->nb_philo)
		{
			pthread_mutex_lock(&var->last_eat[i_philo]);
			if (var->philo[i_philo].t_last_eat != 0)
			{
				if (get_time_elapsed(var->philo[i_philo].t_last_eat)
					>= (long long) var->time_die)
				{
					print_death(var, var->philo[i_philo].id);
					return ;
				}
			}
			pthread_mutex_unlock(&var->last_eat[i_philo]);
		}
		pthread_mutex_lock(&var->check_end_eating);
	}
	pthread_mutex_unlock(&var->check_end_eating);
	write(1, "All philosophers have eaten well !\n", 35);
}

static int	exit_philo(t_var *var, int last_philo)
{
	int	i_philo;

	i_philo = -1;
	while (++i_philo < last_philo)
		pthread_join(var->philo[i_philo].thread_id, NULL);
	destroy_all(var);
	free_all(var, 0);
	return (0);
}

int	run_philosophers(t_var *var)
{
	int		i;
	t_philo	*phi;

	i = -1;
	phi = var->philo;
	while (++i < var->nb_philo)
	{
		if (pthread_create(&phi[i].thread_id, NULL, run_thread, &phi[i]))
		{
			pthread_mutex_lock(&var->writing);
			write(2, "pthread_create error\n", 21);
			var->philo_died = 1;
			pthread_mutex_unlock(&var->writing);
			return (exit_philo(var, i));
		}
	}
	usleep(100);
	wait_thread(var);
	return (exit_philo(var, var->nb_philo));
}
