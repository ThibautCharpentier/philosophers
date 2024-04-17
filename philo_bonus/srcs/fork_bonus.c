/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharpen <tcharpen@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 13:45:10 by tcharpen          #+#    #+#             */
/*   Updated: 2022/08/02 13:45:10 by tcharpen         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

static int	take_forks(t_philo *philo, t_var *var)
{
	sem_wait(var->fork);
	print_change(var, philo, "has taken a fork");
	while (var->nb_philo < 2)
	{
		if (var->nb_philo > 2)
		{
			sem_post(var->fork);
			return (0);
		}
	}
	sem_wait(var->fork);
	print_change(var, philo, "has taken a fork");
	return (1);
}

static void	run_eat(t_philo *philo, t_var *var)
{
	if (!take_forks(philo, var))
		return ;
	sem_wait(var->last_eat);
	print_change(var, philo, "is eating");
	philo->nb_eat = philo->nb_eat + 1;
	if (philo->nb_eat != var->must_eat)
		philo->t_last_eat = get_time();
	else
		philo->t_last_eat = 0;
	sem_post(var->last_eat);
	sem_wait(var->died);
	if (philo->died == 0)
	{
		sem_post(var->died);
		sleep_correctly(var->time_eat * 1000);
	}
	else
		sem_post(var->died);
	sem_post(var->fork);
	sem_post(var->fork);
}

static void	run_sleep(t_philo *philo, t_var *var)
{
	print_change(var, philo, "is sleeping");
	sem_wait(var->died);
	if (philo->died == 0)
	{
		sem_post(var->died);
		sleep_correctly(var->time_sleep * 1000);
	}
	else
		sem_post(var->died);
	print_change(var, philo, "is thinking");
}

void	exit_fork(t_philo *philo, t_var *var, int code)
{
	pthread_join(philo->thread_id, NULL);
	free_all(var);
	exit(code);
}

void	run_fork(t_philo *philo, t_var *var)
{
	if (!var->must_eat)
	{
		free_all(var);
		exit(EXIT_SUCCESS);
	}
	if (pthread_create(&philo->thread_id, NULL, run_thread, philo))
	{
		sem_wait(var->writing);
		free_all(var);
		print_error("pthread_create error\n");
	}
	if (philo->id % 2 == 0)
		run_sleep(philo, var);
	while (philo->nb_eat != var->must_eat)
	{
		run_eat(philo, var);
		if (philo->nb_eat != var->must_eat)
			run_sleep(philo, var);
	}
	exit_fork(philo, var, EXIT_SUCCESS);
}
