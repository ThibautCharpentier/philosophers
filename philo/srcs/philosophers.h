/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharpen <tcharpen@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 12:22:48 by tcharpen          #+#    #+#             */
/*   Updated: 2022/07/26 12:22:48 by tcharpen         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H

# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

/* --------- STRUCT --------- */

typedef struct s_philo
{
	int				id;
	int				nb_eat;
	int				must_eat;
	int				right_fork_id;
	int				left_fork_id;
	long long		t_last_eat;
	pthread_t		thread_id;
	struct s_var	*var;
}				t_philo;

typedef struct s_var
{
	int					nb_philo;
	int					time_die;
	int					time_eat;
	int					time_sleep;
	int					end_eating;
	int					philo_died;
	long long			first_timestamp;
	int					*fork;
	pthread_mutex_t		*last_eat;
	pthread_mutex_t		*check_fork;
	pthread_mutex_t		writing;
	pthread_mutex_t		check_end_eating;
	pthread_mutex_t		check_died;
	t_philo				*philo;
}				t_var;

/* --------- FCT --------- */

/* utils */
int			atoi_philo(char *arg, int nb_error);
void		ft_putchar_fd(char c, int fd);
void		ft_putnbr_fd(long long n, int fd);
size_t		ft_strlen(const char *str);
long long	get_time(void);
long long	get_time_elapsed(long long reference);
void		print_change(t_var *var, int id, char *str);
void		print_death(t_var *var, int id);
void		sleep_correctly(int time);

/* free */
void		free_all(t_var *var, int error);
void		destroy_all(t_var *var);

/* init */
t_var		*init_var(char **arg);
int			init_mutex(t_var *var);
int			init_time(t_var *var);

/* philo */
int			run_philosophers(t_var *var);

/* thread */
void		*run_thread(void *arg);

#endif
