/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharpen <tcharpen@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 18:32:37 by tcharpen          #+#    #+#             */
/*   Updated: 2022/07/26 18:32:37 by tcharpen         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

static int	error_atoi(char *arg)
{
	write(2, arg, ft_strlen(arg));
	write(2, " is not a correct argument\n", 27);
	return (-1);
}

static int	nb_too_high(char *arg, char *cmp)
{
	int	i_arg;

	i_arg = 0;
	while (arg[i_arg] >= '0' && arg[i_arg] <= '9')
	{
		if (arg[i_arg] < cmp[i_arg])
			return (0);
		else if (arg[i_arg] > cmp[i_arg])
			return (1);
		i_arg++;
	}
	return (0);
}

static int	add_res(int i_arg, char *arg, long *res)
{
	int	nb_digit;

	nb_digit = 0;
	while (arg[i_arg] >= '0' && arg[i_arg] <= '9')
	{
		*res = *res * 10 + arg[i_arg] - '0';
		nb_digit++;
		if (nb_digit == 11)
			return (error_atoi(arg));
		i_arg++;
	}
	if (arg[i_arg])
		return (error_atoi(arg));
	else if (nb_digit == 10)
	{
		if (nb_too_high(arg + i_arg - 10, "2147483647"))
			return (error_atoi(arg));
	}
	return (1);
}

int	atoi_philo(char *arg, int nb_error)
{
	int		i_arg;
	long	res;

	res = 0;
	i_arg = 0;
	while (arg[i_arg] == ' ' || arg[i_arg] == '\f' || arg[i_arg] == '\n'
		|| arg[i_arg] == '\r' || arg[i_arg] == '\t' || arg[i_arg] == '\v')
		i_arg++;
	if (arg[i_arg] == '+' || arg[i_arg] == '-')
	{
		if (arg[i_arg] == '-')
			return (error_atoi(arg));
		i_arg++;
	}
	while (arg[i_arg] == '0')
		i_arg++;
	if (add_res(i_arg, arg, &res) < 0)
		return (-1);
	if ((!res && nb_error != 2) || (res > 200 && nb_error == 1))
		return (error_atoi(arg));
	return (res);
}
