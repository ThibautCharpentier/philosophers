/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharpen <tcharpen@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 13:07:44 by tcharpen          #+#    #+#             */
/*   Updated: 2022/08/02 13:07:44 by tcharpen         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

static void	error_time(t_philo *philo, t_var *var)
{
	sem_wait(var->writing);
	sem_wait(var->died);
	philo->died = 1;
	write(2, "gettimeofday error\n", 19);
	exit(EXIT_FAILURE);
}

void	*run_thread(void *arg)
{
	t_var		*var;
	long long	time;
	t_philo		*philo;

	philo = (t_philo *) arg;
	var = philo->var;
	while (1)
	{
		sem_wait(var->last_eat);
		if (philo->t_last_eat == 0)
		{
			sem_post(var->last_eat);
			return (NULL);
		}
		time = get_time_elapsed(philo->t_last_eat);
		if (time < 0)
			error_time(philo, var);
		else if (time >= (long long) var->time_die)
			print_death(philo, var);
		sem_post(var->last_eat);
	}
	return (NULL);
}
