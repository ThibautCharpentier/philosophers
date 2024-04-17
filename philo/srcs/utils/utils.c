/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharpen <tcharpen@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 19:56:00 by tcharpen          #+#    #+#             */
/*   Updated: 2022/07/26 19:56:00 by tcharpen         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

long long	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
	{
		write(2, "gettimeofday error\n", 19);
		return (-1);
	}
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

long long	get_time_elapsed(long long reference)
{
	return (get_time() - reference);
}

void	print_change(t_var *var, int id, char *str)
{
	pthread_mutex_lock(&var->writing);
	if (var->philo_died == 0)
	{
		ft_putnbr_fd(get_time_elapsed(var->first_timestamp), 1);
		write(1, "ms ", 3);
		ft_putnbr_fd((long long) id, 1);
		write(1, " ", 1);
		write(1, str, ft_strlen(str));
		write(1, "\n", 1);
	}
	pthread_mutex_unlock(&var->writing);
}

void	print_death(t_var *var, int id)
{
	pthread_mutex_lock(&var->writing);
	pthread_mutex_lock(&var->check_died);
	var->philo_died = 1;
	pthread_mutex_unlock(&var->check_died);
	ft_putnbr_fd(get_time_elapsed(var->first_timestamp), 1);
	write(1, "ms ", 3);
	ft_putnbr_fd((long long) id, 1);
	write(1, " died\n", 6);
	pthread_mutex_unlock(&var->last_eat[id - 1]);
	pthread_mutex_unlock(&var->writing);
}

void	sleep_correctly(int time)
{
	long long	reference;

	reference = get_time();
	while (get_time_elapsed(reference) * 1000 < time)
		usleep(100);
}
