/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharpen <tcharpen@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 13:45:46 by tcharpen          #+#    #+#             */
/*   Updated: 2022/08/02 13:45:46 by tcharpen         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

static void	init_int(t_var *var, char **arg)
{
	var->nb_philo = atoi_philo(arg[1], 1);
	var->time_die = atoi_philo(arg[2], 0);
	var->time_eat = atoi_philo(arg[3], 0);
	var->time_sleep = atoi_philo(arg[4], 0);
	var->must_eat = -2;
	if (arg[5])
		var->must_eat = atoi_philo(arg[5], 2);
	if (var->nb_philo < 0 || var->time_die < 0 || var->time_eat < 0
		|| var->time_sleep < 0 || var->must_eat == -1)
	{
		free(var);
		exit(EXIT_FAILURE);
	}
}

static void	init_philo(t_var *var)
{
	int	i_philo;

	i_philo = -1;
	while (++i_philo < var->nb_philo)
	{
		var->philo[i_philo].nb_eat = 0;
		var->philo[i_philo].id = i_philo + 1;
		var->philo[i_philo].died = 0;
		var->philo[i_philo].var = var;
	}
}

static void	init_sem(t_var *var)
{
	sem_unlink("sem_last_eat");
	sem_unlink("sem_fork");
	sem_unlink("sem_writing");
	sem_unlink("sem_died");
	var->last_eat = sem_open("sem_last_eat", O_CREAT, S_IRWXU, 1);
	var->fork = sem_open("sem_fork", O_CREAT, S_IRWXU, var->nb_philo);
	var->writing = sem_open("sem_writing", O_CREAT, S_IRWXU, 1);
	var->died = sem_open("sem_died", O_CREAT, S_IRWXU, 1);
	if (var->last_eat == SEM_FAILED || var->fork == SEM_FAILED
		|| var->writing == SEM_FAILED || var->died == SEM_FAILED)
	{
		destroy_sem(var);
		free_all(var);
		print_error("sem_open error\n");
	}
}

static void	init_time(t_var *var)
{
	int	i_philo;

	var->first_timestamp = get_time();
	if (var->first_timestamp < 0)
	{
		free_all(var);
		print_error("gettimeofday error\n");
	}
	i_philo = -1;
	while (++i_philo < var->nb_philo)
		var->philo[i_philo].t_last_eat = var->first_timestamp;
}

t_var	*init_var(char **arg)
{
	t_var	*var;

	var = malloc(sizeof(t_var) * 1);
	if (!var)
		print_error("malloc error\n");
	init_int(var, arg);
	var->philo = malloc(sizeof(t_philo) * var->nb_philo);
	if (!var->philo)
	{
		free_all(var);
		print_error("malloc error\n");
	}
	init_philo(var);
	init_sem(var);
	init_time(var);
	return (var);
}
