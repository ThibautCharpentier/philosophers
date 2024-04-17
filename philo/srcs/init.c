/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharpen <tcharpen@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 17:58:44 by tcharpen          #+#    #+#             */
/*   Updated: 2022/07/26 17:58:44 by tcharpen         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	init_int(t_var *var, int *must_eat, char **arg)
{
	var->fork = NULL;
	var->last_eat = NULL;
	var->end_eating = 0;
	var->philo_died = 0;
	var->nb_philo = atoi_philo(arg[1], 1);
	var->time_die = atoi_philo(arg[2], 0);
	var->time_eat = atoi_philo(arg[3], 0);
	var->time_sleep = atoi_philo(arg[4], 0);
	*must_eat = -2;
	if (arg[5])
		*must_eat = atoi_philo(arg[5], 2);
	if (var->nb_philo < 0 || var->time_die < 0 || var->time_eat < 0
		|| var->time_sleep < 0 || *must_eat == -1)
	{
		free(var);
		return (0);
	}
	return (1);
}

static void	init_philo(t_var *var, int must_eat)
{
	int	i_philo;

	i_philo = -1;
	while (++i_philo < var->nb_philo)
	{
		var->philo[i_philo].var = var;
		var->philo[i_philo].must_eat = must_eat;
		var->philo[i_philo].nb_eat = 0;
		var->philo[i_philo].id = i_philo + 1;
		var->philo[i_philo].right_fork_id = i_philo;
		var->philo[i_philo].left_fork_id = i_philo + 1;
		if (i_philo == var->nb_philo - 1)
			var->philo[i_philo].left_fork_id = 0;
	}
}

t_var	*init_var(char **arg)
{
	t_var	*var;
	int		must_eat;

	var = malloc(sizeof(t_var) * 1);
	if (!var)
	{
		write(2, "malloc error\n", 13);
		return (NULL);
	}
	if (!init_int(var, &must_eat, arg))
		return (NULL);
	var->philo = malloc(sizeof(t_philo) * var->nb_philo);
	if (!var->philo)
	{
		free_all(var, 1);
		return (NULL);
	}
	init_philo(var, must_eat);
	return (var);
}

int	init_mutex(t_var *var)
{
	int	i;

	var->check_fork = malloc(sizeof(pthread_mutex_t) * var->nb_philo);
	var->last_eat = malloc(sizeof(pthread_mutex_t) * var->nb_philo);
	var->fork = malloc(sizeof(int) * var->nb_philo);
	if (!var->check_fork || !var->last_eat || !var->fork)
	{
		free_all(var, 1);
		return (0);
	}
	pthread_mutex_init(&var->writing, NULL);
	pthread_mutex_init(&var->check_end_eating, NULL);
	pthread_mutex_init(&var->check_died, NULL);
	i = -1;
	while (++i < var->nb_philo)
	{
		pthread_mutex_init(&var->check_fork[i], NULL);
		pthread_mutex_init(&var->last_eat[i], NULL);
		var->fork[i] = 1;
	}
	return (1);
}

int	init_time(t_var *var)
{
	int	i_philo;

	var->first_timestamp = get_time();
	if (var->first_timestamp < 0)
	{
		destroy_all(var);
		free_all(var, 0);
		return (0);
	}
	i_philo = -1;
	while (++i_philo < var->nb_philo)
		var->philo[i_philo].t_last_eat = var->first_timestamp;
	return (1);
}
