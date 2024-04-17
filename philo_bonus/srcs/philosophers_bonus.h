/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharpen <tcharpen@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 13:46:19 by tcharpen          #+#    #+#             */
/*   Updated: 2022/08/02 13:46:19 by tcharpen         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_BONUS_H

# define PHILOSOPHERS_BONUS_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>

/* --------- STRUCT --------- */

typedef struct s_philo
{
	int				id;
	int				nb_eat;
	int				died;
	long long		t_last_eat;
	pthread_t		thread_id;
	pid_t			pid;
	struct s_var	*var;
}				t_philo;

typedef struct s_var
{
	int			nb_philo;
	int			time_die;
	int			time_eat;
	int			time_sleep;
	int			must_eat;
	long long	first_timestamp;
	sem_t		*last_eat;
	sem_t		*fork;
	sem_t		*writing;
	sem_t		*died;
	t_philo		*philo;
}				t_var;

/* --------- FCT --------- */

/* utils */
int			atoi_philo(char *arg, int nb_error);
void		ft_putchar_fd(char c, int fd);
void		ft_putnbr_fd(long long n, int fd);
size_t		ft_strlen(const char *str);
long long	get_time(void);
long long	get_time_elapsed(long long reference);
void		print_change(t_var *var, t_philo *philo, char *str);
void		*print_death(t_philo *philo, t_var *var);
void		sleep_correctly(int time);

/* free */
void		print_error(char *error);
void		free_all(t_var *var);
void		destroy_sem(t_var *var);
void		destroy_fork(t_var *var, int nb_fork);

/* init */
t_var		*init_var(char **arg);

/* philo */
void		run_philosophers(t_var *var);

/* fork */
void		run_fork(t_philo *philo, t_var *var);
void		exit_fork(t_philo *philo, t_var *var, int code);

/* thread */
void		*run_thread(void *arg);

#endif
