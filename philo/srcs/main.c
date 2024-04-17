/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharpen <tcharpen@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 17:35:54 by tcharpen          #+#    #+#             */
/*   Updated: 2022/07/26 17:35:54 by tcharpen         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_var	*var;

	if (argc != 5 && argc != 6)
	{
		write(2, "Execute 'philo' with four or five arguments\n", 44);
		return (1);
	}
	else
	{
		var = init_var(argv);
		if (!var)
			return (1);
		if (!init_mutex(var))
			return (1);
		if (!init_time(var))
			return (1);
		return (run_philosophers(var));
	}
	return (0);
}
