/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharpen <tcharpen@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 13:44:57 by tcharpen          #+#    #+#             */
/*   Updated: 2022/08/02 13:44:57 by tcharpen         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers_bonus.h"

long long	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (-1);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

long long	get_time_elapsed(long long reference)
{
	long long	time;

	time = get_time();
	if (time < 0)
		return (-1);
	return (get_time() - reference);
}

void	print_change(t_var *var, t_philo *philo, char *str)
{
	long long	time;

	sem_wait(var->writing);
	if (philo->died == 0)
	{
		time = get_time_elapsed(var->first_timestamp);
		if (time < 0)
		{
			write(2, "gettimeofday error\n", 19);
			exit_fork(philo, var, EXIT_FAILURE);
		}
		ft_putnbr_fd(time, 1);
		write(1, "ms ", 3);
		ft_putnbr_fd((long long) philo->id, 1);
		write(1, " ", 1);
		write(1, str, ft_strlen(str));
		write(1, "\n", 1);
	}
	sem_post(var->writing);
}

void	*print_death(t_philo *philo, t_var *var)
{
	sem_wait(var->writing);
	sem_wait(var->died);
	philo->died = 1;
	ft_putnbr_fd(get_time_elapsed(var->first_timestamp), 1);
	write(1, "ms ", 3);
	ft_putnbr_fd((long long) philo->id, 1);
	write(1, " died\n", 6);
	exit(EXIT_FAILURE);
}

void	sleep_correctly(int time)
{
	long long	reference;

	reference = get_time();
	while (get_time_elapsed(reference) * 1000 < time)
		usleep(100);
}
