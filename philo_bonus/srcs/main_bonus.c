/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharpen <tcharpen@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 13:46:00 by tcharpen          #+#    #+#             */
/*   Updated: 2022/08/02 13:46:00 by tcharpen         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int	main(int argc, char **argv)
{
	t_var	*var;

	if (argc != 5 && argc != 6)
	{
		print_error("Execute 'philo_bonus' with four or five arguments\n");
		return (1);
	}
	else
	{
		var = init_var(argv);
		run_philosophers(var);
	}
	return (0);
}
