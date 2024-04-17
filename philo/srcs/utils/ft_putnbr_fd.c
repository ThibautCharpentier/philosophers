/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharpen <tcharpen@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 11:39:12 by tcharpen          #+#    #+#             */
/*   Updated: 2022/07/29 11:39:12 by tcharpen         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	ft_putnbr_fd(long long n, int fd)
{
	unsigned long long	nbr;

	if (n < 0)
	{
		nbr = -n;
		ft_putchar_fd('-', fd);
	}
	else
		nbr = n;
	if (nbr > 9)
	{
		ft_putnbr_fd(nbr / 10, fd);
		nbr = nbr % 10;
	}
	ft_putchar_fd(nbr + 48, fd);
}
