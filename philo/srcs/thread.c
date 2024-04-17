/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharpen <tcharpen@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 17:03:41 by tcharpen          #+#    #+#             */
/*   Updated: 2022/07/27 17:03:41 by tcharpen         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	take_forks(t_philo *philo, t_var *var)
{
	pthread_mutex_lock(&var->check_fork[philo->right_fork_id]);
	var->fork[philo->right_fork_id] = 0;
	print_change(var, philo->id, "has taken a fork");
	while (var->nb_philo < 2)
	{
		pthread_mutex_lock(&var->check_died);
		if (var->philo_died == 1)
		{
			var->fork[philo->right_fork_id] = 1;
			pthread_mutex_unlock(&var->check_fork[philo->right_fork_id]);
			pthread_mutex_unlock(&var->check_died);
			return (0);
		}
		pthread_mutex_unlock(&var->check_died);
	}
	pthread_mutex_lock(&var->check_fork[philo->left_fork_id]);
	var->fork[philo->left_fork_id] = 0;
	print_change(var, philo->id, "has taken a fork");
	return (1);
}

static void	run_eat(t_philo *philo, t_var *var)
{
	if (!take_forks(philo, var))
		return ;
	pthread_mutex_lock(&var->last_eat[philo->id - 1]);
	print_change(var, philo->id, "is eating");
	philo->nb_eat = philo->nb_eat + 1;
	if (philo->nb_eat != philo->must_eat)
		philo->t_last_eat = get_time();
	else
		philo->t_last_eat = 0;
	pthread_mutex_unlock(&var->last_eat[philo->id - 1]);
	pthread_mutex_lock(&var->check_died);
	if (var->philo_died == 0)
	{
		pthread_mutex_unlock(&var->check_died);
		sleep_correctly(var->time_eat * 1000);
	}
	else
		pthread_mutex_unlock(&var->check_died);
	var->fork[philo->right_fork_id] = 1;
	var->fork[philo->left_fork_id] = 1;
	pthread_mutex_unlock(&var->check_fork[philo->right_fork_id]);
	pthread_mutex_unlock(&var->check_fork[philo->left_fork_id]);
}

static void	run_sleep(t_philo *philo, t_var *var)
{
	print_change(var, philo->id, "is sleeping");
	pthread_mutex_lock(&var->check_died);
	if (var->philo_died == 1)
	{
		pthread_mutex_unlock(&var->check_died);
		return ;
	}
	pthread_mutex_unlock(&var->check_died);
	sleep_correctly(var->time_sleep * 1000);
	print_change(var, philo->id, "is thinking");
}

static int	run_cycle(t_var *var, t_philo *philo)
{
	while (philo->nb_eat != philo->must_eat && philo->must_eat)
	{
		run_eat(philo, var);
		if (philo->nb_eat != philo->must_eat)
			run_sleep(philo, var);
		pthread_mutex_lock(&var->check_died);
		if (var->philo_died == 1)
		{
			pthread_mutex_unlock(&var->check_died);
			return (0);
		}
		pthread_mutex_unlock(&var->check_died);
	}
	return (1);
}

void	*run_thread(void *arg)
{
	t_philo	*philo;
	t_var	*var;

	philo = (t_philo *) arg;
	var = philo->var;
	if (!philo->must_eat)
	{
		pthread_mutex_lock(&var->last_eat[philo->id - 1]);
		philo->t_last_eat = 0;
		pthread_mutex_unlock(&var->last_eat[philo->id - 1]);
	}
	else if (philo->id % 2 == 0 && philo->nb_eat != philo->must_eat)
		run_sleep(philo, var);
	if (!run_cycle(var, philo))
		return (NULL);
	pthread_mutex_lock(&var->check_end_eating);
	var->end_eating = var->end_eating + 1;
	pthread_mutex_unlock(&var->check_end_eating);
	return (NULL);
}
