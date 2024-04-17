/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharpen <tcharpen@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 13:45:29 by tcharpen          #+#    #+#             */
/*   Updated: 2022/08/02 13:45:29 by tcharpen         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	print_error(char *error)
{
	write(2, error, ft_strlen(error));
	exit(EXIT_FAILURE);
}

void	free_all(t_var *var)
{
	free(var->philo);
	free(var);
}

void	destroy_sem(t_var *var)
{
	sem_close(var->last_eat);
	sem_close(var->fork);
	sem_close(var->writing);
	sem_close(var->died);
	sem_unlink("sem_last_eat");
	sem_unlink("sem_fork");
	sem_unlink("sem_writing");
	sem_unlink("sem_died");
}

void	destroy_fork(t_var *var, int nb_fork)
{
	int	i;

	i = -1;
	while (++i < nb_fork)
		kill(var->philo[i].pid, SIGTERM);
}
