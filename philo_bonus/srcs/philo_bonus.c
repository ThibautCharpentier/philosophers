/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharpen <tcharpen@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 13:46:08 by tcharpen          #+#    #+#             */
/*   Updated: 2022/08/02 13:46:08 by tcharpen         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

static void	exit_philo(t_var *var, int last_philo)
{
	int	i_philo;
	int	status;

	i_philo = -1;
	while (++i_philo < last_philo)
	{
		if (waitpid(-1, &status, 0) < 0)
		{
			destroy_fork(var, last_philo);
			destroy_sem(var);
			free_all(var);
			print_error("waitpid error\n");
		}
		if (WEXITSTATUS(status) == EXIT_FAILURE)
		{
			destroy_fork(var, last_philo);
			break ;
		}
	}
	if (i_philo == last_philo)
		write(1, "All philosophers have eaten well !\n", 35);
	destroy_sem(var);
	free_all(var);
	exit(EXIT_SUCCESS);
}

void	run_philosophers(t_var *var)
{
	int		i;

	i = -1;
	while (++i < var->nb_philo)
	{
		var->philo[i].pid = fork();
		if (var->philo[i].pid == -1)
		{
			destroy_fork(var, i);
			destroy_sem(var);
			free_all(var);
			print_error("fork error\n");
		}
		else if (var->philo[i].pid == 0)
			run_fork(&var->philo[i], var);
	}
	exit_philo(var, var->nb_philo);
}
